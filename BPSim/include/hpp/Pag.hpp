#include <PredictorInterface.hpp>
#include <PatternAutomatons.hpp>
#include <BPBaseCache.hpp>
#include <cassert>


class PagPredictor : public PredictorInterface{

    public:
        PagPredictor(std::size_t bhrLength, std::size_t phtlegth, std::size_t BHTentryCount, 
        BPBaseCache bht, PatternAutomaton pattern);      

        virtual void predictBranch(uint64_t branchAddress, bool actualDirection) override;
        virtual void printStatistics()  override;
        ~PagPredictor() = default;

    private: 
        std::size_t BHTEntryCount{0};
        std::size_t BHRLength{5};
        std::size_t patternLength{0};
        BPBaseCache PHT;
        BPBaseCache BHT;
        PatternAutomaton patternAutomataton;
        
        inline static const uint64_t  MASKCONST{0xFFFF'FFFF'FFFF'FFFF};
        uint64_t  bhrMask{0};
        //static const 
};