#pragma once
#include <Associative.hpp>
#include <ReplacementPolicy.hpp>
#include <memory>
#include <algorithm>


class IdealLRU : public ReplacementPolicy{
    public :
        IdealLRU(Associative& ); 
        void trackLRU(const std::size_t &, const int&) override;
        int Replace(const std::size_t  &)override;
        std::string policyName() override; 
    private:
        std::vector<int> handlingMeta;
        int associativity{0};
        int numOfEntries{0};
        std::size_t flatIndex{0};
        //std::unique_ptr<Associative> assocPtr;
        //helper
};