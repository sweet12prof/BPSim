
#include <print>
#include <random>
#include <string>
#include <Pag.hpp>
#include <bitset>
#include <array>


int main(){

    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<int> dist {0, 1};
    std::bernoulli_distribution dist2{0.5};
    uint64_t someRand{0xCA98F466};
     
     BPBaseCache BHT(32, 6, 2, -1, TableType::ASSOCIATIVE, ReplacementPolicy::LRU);
     PatternAutomaton pattern(2, AutomatonTypes::TWO_BIT_GENERIC);
     PagPredictor Pag(6, 2, 32, BHT, pattern);

    std::array<int, 32> predPattern {0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0};
//    std::array<int, 32> predPattern;
//    for(auto &item : predPattern)
//         item = dist(engine);
//0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0

//    int j =0;
    for (int i{0}; i<10000;){
        i++;
        bool k = (bool)predPattern[((i)%32)];
        // if(j == 31)
        //     j = 0;
        // else j++;
         Pag.predictBranch(someRand, k);
    }
       
    
    Pag.printStatistics();
    
 
}

// #include <iostream>
// #include <vector>
// #include <unordered_set>
// #include <string>

// bool hasRepeating5BitPattern(const std::vector<int>& sequence) {
//     std::unordered_set<std::string> seenPatterns;
//     int size = sequence.size();

//     for (int i = 0; i < size; ++i) {
//         // Form 5-bit window, accounting for wraparound
//         std::string pattern = "";
//         for (int j = 0; j < 5; ++j) {
//             pattern += std::to_string(sequence[(i + j) % size]);
//         }

//         // Check if the pattern has been seen before
//         if (seenPatterns.find(pattern) != seenPatterns.end()) {
//             return true;  // Found repeating pattern
//         }
//         seenPatterns.insert(pattern);
//     }

//     return false;  // No repeating patterns
// }

// std::vector<int> generateNonRepeatingSequence(int length) {
//     std::vector<int> sequence(length);

//     // Try different patterns until we find a valid sequence
//     do {
//         // Randomly fill the sequence with 0s and 1s
//         for (int i = 0; i < length; ++i) {
//             sequence[i] = rand() % 2;  // Generate 0 or 1 randomly
//         }
//     } while (hasRepeating5BitPattern(sequence));  // Keep trying until we find a valid one

//     return sequence;
// }

// int main() {
//     int length = 32;  // Length of the sequence
//     std::vector<int> sequence = generateNonRepeatingSequence(length);

//     // Print the sequence as a comma-separated list
//     for (int i = 0; i < length; ++i) {
//         std::cout << sequence[i];
//         if (i < length - 1) std::cout << ", ";
//     }
//     std::cout << std::endl;

//     return 0;
// }