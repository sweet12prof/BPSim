#include <BPBaseCache.hpp>
#include <print>
#include <random>
#include <string>

int main(){

    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<uint32_t> dist {0x1020345, 0xFFFFFFFF};

    // uint64_t someRand{static_cast<uint64_t>(dist(engine))};
    uint64_t someRand{0xCA98F466};

    BPBaseCache cache(128, 5, 1, -1, TableType::HASHEDplusTAG, ReplacementPolicy::HASHED);  
    //uint64_t data {cache.getEantry(someRand)};
    std::print("The data was {}", cache.getEantry(someRand).found ? "found" : "not found");
}