#include <cstdint>
#include <cstddef>
#include <bitset>

enum class AutomatonTypes{
    LASTTIME, 
    TWO_BIT_GENERIC
};

class PatternAutomaton{
    private:
        std::size_t phtEntryLength{2};
        AutomatonTypes automaton{AutomatonTypes::TWO_BIT_GENERIC};
    public:
        PatternAutomaton(std::size_t phtEntryLength, AutomatonTypes automaton);
        bool getPrediction(std::uint64_t phtEntry);
        std::uint64_t getNewPhtBits(bool actualdirection, std::uint64_t currBits);
};