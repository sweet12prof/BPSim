#pragma once
#include <bitset>
#include <string>
//template <std::size_t tagSize>
struct cacheline
{   
    char validBit{'0'}, dirtyBit{'0'};
    std::string tag{""}; 
};


