#include <BPBaseCache.hpp>
#include <PredictorInterface.hpp>

class PagPredictor : public PredictorInterface{

    public:
        PagPredictor(std::size_t bhrLength, std::size_t phtlegth, std::size_t BHTentryCount, 
        BPBaseCache bht, BPBaseCache pht);      

        virtual void predictBranch(uint64_t branchAddress, bool actualDirection) override;
        virtual void evaluateAndUpdateTable(bool actualDirection) override;
        void printStatistics() const override;  
        ~PagPredictor() = default;

    private: 
        std::size_t BHTEntryCount;
        std::size_t BHRLength;
        std::size_t patternLength;
        BPBaseCache PHT;
        BPBaseCache BHT;
};