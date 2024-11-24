#include <cstdint>
class PredictorInterface{
    protected:
        uint64_t      goodPred{0}, 
                      failPred{0}, 
                      tableHits{0}, 
                      tableMisses{0}, 
                      overallAcesses{0};
        float         accuracyRatio{0.0}, 
                      HitRatio{0.0};
    public:
        virtual void predictBranch(uint64_t branchAddress, bool actualDirection) = 0;
        virtual void evaluateAndUpdateTable(bool actualDirection);
        virtual void printStatistics() const;
        virtual ~PredictorInterface() = default; 
};