#include <BPBaseStruct.hpp>
#include <vector>
#include <cmath>
#include <bitset>
#include <print>
#include <random>


class BPBaseCache{
    public:
        BPBaseCache(std::size_t numofEntries, std::size_t BPEntryLength, 
        int associativity, int cacheSize, TableType tableType, ReplacementPolicy policy); 
       
        BPentryReturnVal getEantry(uint64_t address);
        void replaceEntry(uint64_t address, uint32_t entryData);

        void replacePolicyHASHED(uint64_t index, uint64_t entryData);
        void replacePolicyLRU(uint64_t index, uint64_t tag,  uint32_t entryData);
        void replacePolicyRANDOM(uint64_t index, uint64_t tag, uint32_t entryData);


    private:
        std::vector<BPBaseStruct> bTable;
        std::size_t numOfEntries         {256};             //Number of entries in table 
        std::size_t BPEntryLength        {5};               //entry length of data field in BP struct
        std::size_t BPTagLength          {0};               //tag length in the BP struct 
        std::size_t BPTagLength_shift    {0}; 
        std::size_t BPIndexLength        {8};               //length of index bits
        std::size_t BPflatIndexLength    {0};
        TableType tblType                {TableType::HASHED}; 
        ReplacementPolicy   ReplacePolicy{ReplacementPolicy::HASHED};
        int associativity                {1};               //associativity of table 
        int cacheSize                    {-1};               // size of table in bytes
        std::size_t assocBitLength       {0};
        std::size_t effectiveTableLength {256};
        
        inline const static std::size_t BPInstructionAddressWidth{32};
        inline const static std::size_t uintcorrection {64- BPBaseCache::BPInstructionAddressWidth};
};