#pragma once
#include <cacheline.hpp>
#include <vector>
class ReplacementPolicy{
    public: 
        virtual ~ReplacementPolicy() = default;
        virtual void trackLRU(const std::size_t &, const int&) = 0;
        virtual int  Replace(const std::size_t  &) = 0;
        virtual std::string policyName() = 0;
};