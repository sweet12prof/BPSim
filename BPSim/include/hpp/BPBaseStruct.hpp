//--Base data structure for branch prediction Cache 
#include <string>
enum class TableType{
    HASHED,
    HASHEDplusTAG,
    ASSOCIATIVE
};

enum class ReplacementPolicy{
    HASHED, 
    RANDOM, 
    LRU
};

struct BPBaseStruct{
    uint64_t tag{0xCA98F4};
    uint32_t data{0};
    uint32_t lrutrack{0};
};

struct BPentryReturnVal
{
    uint32_t data;
    bool found;
};
