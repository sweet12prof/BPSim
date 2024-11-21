#pragma once
#include <ReplacementPolicy.hpp>
#include <Associative.hpp>


class RandomReplacement : public ReplacementPolicy{
    public:
        RandomReplacement(Associative& );
        int Replace(const std::size_t& ) override;
        void trackLRU(const std::size_t &, const int&) override;
        std::string policyName() override;
    private: 
        int associativity{0};
        int randWay{-1};

};