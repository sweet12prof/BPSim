#include <Pag.hpp>

PagPredictor::PagPredictor(std::size_t bhrLength, std::size_t phtlegth, std::size_t bhtentryCount, 
    BPBaseCache bht, BPBaseCache pht) :BHTEntryCount(bhtentryCount), BHRLength(bhrLength), 
    patternLength(phtlegth), 
    PHT((2^BHRLength), phtlegth, 1, -1, TableType::HASHED, ReplacementPolicy::HASHED), BHT(bht){}

void PagPredictor::predictBranch(std::uint64_t branchAddress, bool actualDirection){
    BPentryReturnVal val {PagPredictor::BHT.getEantry(branchAddress)};
    uint64_t mask{0xE}, temp{0};
    bool tempDirection{false};
    if(val.found)
        {
            PagPredictor::tableHits++;
            temp =  mask & val.data;
            tempDirection = (temp == 0) ? false : true;
            if(tempDirection == actualDirection)
                PagPredictor::goodPred++;
            else 
                PagPredictor::failPred++;
        }
}