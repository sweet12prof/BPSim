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

    BPBaseCache cache(128, 5, 4, -1, TableType::HASHEDplusTAG, ReplacementPolicy::LRU);  
    //uint64_t data {cache.getEantry(someRand)};
    cache.replaceEntry(someRand, 33);
     cache.replaceEntry((someRand + (6*128)), 13);
     cache.replaceEntry((someRand + (4*128)), 03);
     cache.replaceEntry((someRand + (2*128)), 53);
     cache.replaceEntry((someRand + (3*128)), 23);
    std::print("The data was {}", cache.getEantry(someRand+(2*128)).found ? "found" : "not found");
}