#include <Pag.hpp>

PagPredictor::PagPredictor(std::size_t bhrLength, std::size_t phtlegth, std::size_t bhtentryCount, 
    BPBaseCache bht, PatternAutomaton pattern) 
    :BHTEntryCount(bhtentryCount), BHRLength(bhrLength), patternLength(phtlegth), 
    PHT((std::pow(2, (bhrLength-1))), phtlegth, 1, -1, TableType::HASHED, ReplacementPolicy::HASHED), BHT(bht), 
    patternAutomataton(pattern), bhrMask((PagPredictor::MASKCONST << (64 - bhrLength)) >>  (64 - bhrLength))
    {
        this->BHT.InitBPTable(std::pow(2, bhrLength) - 1);
        this->PHT.InitBPTable((std::pow(2, phtlegth)/2)-1);
    }

void PagPredictor::predictBranch(std::uint64_t branchAddress, bool actualDirection){
    BPentryReturnVal val {PagPredictor::BHT.getEantry(branchAddress)};
    uint64_t mask{0x1}, temp{0};
    bool tempDirection{false};
    if(val.found)
        {
            PagPredictor::tableHits++;
            temp =  mask & val.data;
            assert(temp >=0 && temp <2);

            tempDirection = (temp == 0) ? false : true;

            if(tempDirection == actualDirection)
                PagPredictor::goodPred++;
            else 
                  PagPredictor::failPred++;            
    }
    else 
        {
            this->tableMisses++;
            this->BHT.replaceEntry(branchAddress, mask); //create new entry
        }
    
    val = PagPredictor::BHT.getEantry(branchAddress);           //read again to account for entries that werent found initially, in associative tagged tables
    uint64_t bhrCurrEntry {PagPredictor::bhrMask & val.data};   //actual content of bhr
    
    bhrCurrEntry = (bhrCurrEntry >> 1) ;                        //bhr shifted to remove old pred bit
     assert(bhrCurrEntry >= 0 && bhrCurrEntry < std::pow(2, (this->BHRLength-1)));
    uint64_t currPHT{this->PHT.getEantry(bhrCurrEntry).data};   //pht bits for curr bhr
    this->PHT.modifyDataEntry(bhrCurrEntry ,patternAutomataton.getNewPhtBits(actualDirection, currPHT)); //update pht entry for curr bhr

    bhrCurrEntry = bhrCurrEntry << 1;

     if (bhrCurrEntry >= std::pow(2, (this->BHRLength -1)))
         bhrCurrEntry = (bhrCurrEntry) -  std::pow(2, (this->BHRLength-1)); //1-BIT lsB to append recent actual dir


     if(actualDirection)
        bhrCurrEntry = bhrCurrEntry | 0x1; //reent direction appended into LSB
    
   
    std::uint64_t patt{this->PHT.getEantry(bhrCurrEntry).data};      //get new pattern entry for new bhr entry
    bool nextPredForCurrBHR{patternAutomataton.getPrediction(patt)}; //direction next time we see current bhr content

    bhrCurrEntry =  bhrCurrEntry << 1; //1-BIT Lsb for next prediction bit of new bhr content
    if (bhrCurrEntry >= std::pow(2, (this->BHRLength)))
         bhrCurrEntry = (bhrCurrEntry) -  std::pow(2, (this->BHRLength));
    bhrCurrEntry = bhrCurrEntry | static_cast<uint64_t>(nextPredForCurrBHR);
    
    assert(bhrCurrEntry >= 0 && bhrCurrEntry < std::pow(2, (this->BHRLength)));
    this->BHT.modifyDataEntry(branchAddress, bhrCurrEntry); //STORE ENTRY BACK into table
}

void PagPredictor::printStatistics(){
    std::print("Table Hits              : {}", this->tableHits);
    std::print("\nTable Misses          : {}", this->tableMisses);
    std::print("\nCorrect Predictions   : {}", this->goodPred);
    std::print("\nInCorrect Predictions : {}", this->failPred);
    std::print("\nHit Ratio             : {:.2f}", (double)(this->tableHits)/(this->tableHits + this->tableMisses));
    std::print("\nAccuracy              : {:.2f}", (double)(this->goodPred)/(this->goodPred + this->failPred));
}

