#include <BPBaseCache.hpp>



BPBaseCache::BPBaseCache(std::size_t NumOfEntries, std::size_t BPEntryLength, 
int associativity, int cacheSize, TableType tableType, ReplacementPolicy policy)
:bTable(NumOfEntries * associativity), BPEntryLength(BPEntryLength), numOfEntries(NumOfEntries),
associativity(associativity), cacheSize(cacheSize), tblType(tableType), ReplacePolicy(policy), assocBitLength(std::log2(associativity)){
    if(cacheSize > 0){
        this->numOfEntries = (cacheSize * 8) / (BPEntryLength * associativity);
        this->bTable.resize(this->numOfEntries * associativity);
    }
    this->BPIndexLength       = std::log2(this->numOfEntries);
    this->BPflatIndexLength   = (this->BPIndexLength);
    this->BPTagLength_shift   = BPBaseCache::BPInstructionAddressWidth - this->BPflatIndexLength; 
    this->BPTagLength         = (tblType == TableType::HASHED) ? 0 : BPBaseCache::BPInstructionAddressWidth - this->BPflatIndexLength; 
    effectiveTableLength      = this->numOfEntries * this->associativity; 
   // this->assocBitLength      = std::log2(associativity);
}


BPentryReturnVal BPBaseCache::getEantry(uint64_t address) {
    uint64_t temp{0xFFFFFFFF'FFFFFFFF};
    std::uint64_t index{0}, tag{0};
    index = ((temp << (BPTagLength_shift + BPBaseCache::uintcorrection)) >>( BPTagLength_shift + BPBaseCache::uintcorrection)) & address;
    if(tblType != TableType::HASHED)
        {
            tag   = ((temp >> BPflatIndexLength) << BPflatIndexLength) & address;
            tag   =  tag >> BPflatIndexLength;
            std::uint64_t effIndex = (index);
            std::size_t found_Index{NULL};

            for (std::size_t i{effIndex}; i< this->effectiveTableLength; i+= this->numOfEntries){
                 if (tag == bTable[i].tag){
                    if(ReplacePolicy == ReplacementPolicy::LRU) 
                        BPBaseCache::bTable[i].lrutrack = 0;
                    found_Index = i;    
                    break;
                }
                 if(ReplacePolicy == ReplacementPolicy::LRU)
                    bTable[i].lrutrack++;
            }
                return (found_Index == NULL) ? BPentryReturnVal{ 0, false } : BPentryReturnVal{bTable[found_Index].data, true};
        }   
    return { bTable[index].data, true };
}

void BPBaseCache::replaceEntry(uint64_t address, uint64_t entryData){
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


 void BPBaseCache::replacePolicyLRU(uint64_t index, uint64_t tag,  uint64_t entryData){
            uint64_t lruIndex = (index );
            for (std::size_t i{lruIndex+this->numOfEntries}; i <(this->effectiveTableLength); i+= this->numOfEntries){
                if( bTable[lruIndex].lrutrack < bTable[i].lrutrack ){
                    lruIndex = i;
                }
            }
            this->bTable[lruIndex].data     = entryData;
            this->bTable[lruIndex].tag      = tag;
            this->bTable[lruIndex].lrutrack = 0;

            uint64_t lruIndex2 = (index);
            for (std::size_t i{lruIndex2}; i <(this->effectiveTableLength); i+= numOfEntries){
                if(i != lruIndex){
                    this->bTable[i].lrutrack++;
                }
            }
 }

 void BPBaseCache::replacePolicyHASHED(uint64_t index, uint64_t entryData){
    this->bTable[index].data = entryData;
 }

 void BPBaseCache::replacePolicyRANDOM(uint64_t index, uint64_t tag, uint64_t entryData){

        static std::random_device rd;
        static std::default_random_engine engine(rd());
        static std::uniform_int_distribution<int> dist {0, (associativity - 1)};
        
     uint64_t eFFIndex = (index);
     std::size_t randomOffset{static_cast<std::size_t>( dist(engine))};
     eFFIndex += (randomOffset * this->numOfEntries);
      this->bTable[eFFIndex].data = entryData;
      this->bTable[eFFIndex].tag  = tag;

 }


 void BPBaseCache::InitBPTable(uint64_t entryData){
    for(auto &item : bTable)
            item = { .tag{0},.data{entryData}, .lrutrack{0}};
 }