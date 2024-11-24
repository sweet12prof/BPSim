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
    uint64_t tag{0};
    uint64_t data{0};
    uint32_t lrutrack{0};
};

struct BPentryReturnVal
{
    uint64_t data;
    bool found;
};
