#include <PatternAutomatons.hpp>
#include <cassert>

PatternAutomaton::PatternAutomaton(std::size_t phtbitLength, AutomatonTypes automaton)
:phtEntryLength(phtbitLength), automaton{automaton}{}

bool PatternAutomaton::getPrediction(std::uint64_t phtEntry){
    assert(phtEntry >= 0 && phtEntry <4);
    switch(this->phtEntryLength){
        case 1: 
            if(phtEntry == 0x1)
                return true;
            else 
                return false;
        break;

        case 2: 
            if (phtEntry == 0 || phtEntry == 1)
                return  false;
            else if (phtEntry == 2 || phtEntry == 3)
                return true;
            else return false;
        
        default: return false;
    }
}

std::uint64_t PatternAutomaton::getNewPhtBits(bool actualdirection, std::uint64_t currBits){
    switch (this->phtEntryLength){
        
        case 1: return static_cast<uint64_t>(actualdirection);             
        break; 

        case 2:
            //this switch is bad should have switched on the bool instead
            switch(currBits){
                case 0 :
                    if(!actualdirection)
                        return 0;
                    else return 1; 
                break; 

                case 1:
                    if(!actualdirection)
                        return 0;
                    else return 2;
                break;

                case 2: 
                    if(!actualdirection)
                        return 1;
                    else return 3;
                
                case 3: 
                    if(!actualdirection)
                        return 2;
                    else return 3;
                
                default: return 0;
            } 
        break;

        default: return 0;
    }
}