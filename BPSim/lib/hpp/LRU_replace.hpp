#pragma once
#include <ReplacementPolicy.hpp>

class LRU_replace : public ReplacementPolicy
{
    void Replace(const std::vector<cacheline>& set, const std::size_t& address) {
        std::size_t assoc{set.size()};
        // std::size_t
        // for (auto & item : set)
        //     if(item.lruBit)

    }
};