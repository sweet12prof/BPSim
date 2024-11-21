#include <BPBaseCache.hpp>



BPBaseCache::BPBaseCache(std::size_t NumOfEntries, std::size_t BPEntryLength, 
int associativity, int cacheSize, TableType tableType, ReplacementPolicy policy)
:bTable(NumOfEntries * associativity), BPEntryLength(BPEntryLength),
associativity(associativity), cacheSize(cacheSize), tblType(tableType), ReplacePolicy(policy){
    if(cacheSize > 0){
        this->numOfEntries = (cacheSize * 8) / (BPEntryLength * associativity);
        this->bTable.resize(this->numOfEntries * associativity);
    }
    this->BPIndexLength       = std::log2(this->numOfEntries);
    this->BPflatIndexLength   = (this->BPIndexLength + std::log2(associativity));
    this->BPTagLength_shift   = BPBaseCache::BPInstructionAddressWidth - this->BPflatIndexLength; 
    this->BPTagLength         = (tblType == TableType::HASHED) ? 0 : BPBaseCache::BPInstructionAddressWidth - this->BPflatIndexLength; 
}


BPentryReturnVal BPBaseCache::getEantry(uint64_t address) {
    uint64_t temp{0xFFFFFFFF'FFFFFFFF};
    std::uint64_t index{0}, tag{0};
    index = ((temp << (BPTagLength_shift + BPBaseCache::uintcorrection)) >>( BPTagLength_shift + BPBaseCache::uintcorrection)) & address;
    if(tblType != TableType::HASHED)
        {
            tag   = ((temp >> BPflatIndexLength) << BPflatIndexLength) & address;
            tag   =  tag >> BPflatIndexLength;
            std::uint64_t effIndex = (index >> associativity) << associativity;

            for (std::size_t i{effIndex}; i< (effIndex + associativity); i++){
                 if (tag == bTable[i].tag){
                    if(ReplacePolicy == ReplacementPolicy::LRU)
                         BPBaseCache::bTable[i].lrutrack = 0;
                     return {bTable[index].data, true};
                }
                 if(ReplacePolicy == ReplacementPolicy::LRU)
                    bTable[i].lrutrack++;
            }
                return { 0, false };
        }   
    return { bTable[index].data, true };
}

void BPBaseCache::replaceEntry(uint64_t address, uint32_t entryData){
    uint64_t temp{0xFFFFFFFF'FFFFFFFF};
    std::uint64_t index{0}, tag{0};
    index = ((temp << (BPTagLength_shift + BPBaseCache::uintcorrection)) >>( BPTagLength_shift + BPBaseCache::uintcorrection)) & address;
    tag   = ((temp >> BPflatIndexLength) << BPflatIndexLength) & address;
    tag   =  tag >> BPflatIndexLength;

    switch (this->ReplacePolicy)
    {
        case ReplacementPolicy::HASHED:
            BPBaseCache::replacePolicyHASHED(index, entryData);
        break;

        case ReplacementPolicy::LRU : 
            BPBaseCache::replacePolicyLRU(index, tag, entryData);
        break;    

        case ReplacementPolicy::RANDOM : 
            BPBaseCache::replacePolicyRANDOM(index, tag, entryData);
        break;
    
        default:
            BPBaseCache::replacePolicyHASHED(index, entryData);
        break;
    }
}


 void BPBaseCache::replacePolicyLRU(uint64_t index, uint64_t tag,  uint32_t entryData){
            uint64_t lruIndex = (index >> associativity) << associativity;
            for (std::size_t i{lruIndex+1}; i <(index+associativity); i++){
                if( bTable[lruIndex].lrutrack > bTable[i].lrutrack ){
                    lruIndex = i;
                }
            }
            this->bTable[lruIndex].data     = entryData;
            this->bTable[lruIndex].tag      = tag;
            this->bTable[lruIndex].lrutrack = 0;

            uint64_t lruIndex2 = (index >> associativity) << associativity;
            for (std::size_t i{lruIndex2}; i <(index+associativity); i++){
                if(i != lruIndex){
                    this->bTable[i].lrutrack++;
                }
            }
 }

 void BPBaseCache::replacePolicyHASHED(uint64_t index, uint64_t entryData){
    this->bTable[index].data = entryData;
 }

 void BPBaseCache::replacePolicyRANDOM(uint64_t index, uint64_t tag, uint32_t entryData){

        static std::random_device rd;
        static std::default_random_engine engine(rd());
        static std::uniform_int_distribution<int> dist {0, 3};
        
     uint64_t eFFIndex = (index >> associativity) << associativity;
     std::size_t randomOffset{static_cast<std::size_t>( dist(engine))};
     eFFIndex += randomOffset;
      this->bTable[eFFIndex].data = entryData;
      this->bTable[eFFIndex].tag  = tag;

 }