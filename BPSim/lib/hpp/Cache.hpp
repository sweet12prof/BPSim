#pragma once
#include <print>
#include <bitset>
#include <random>

static std::random_device rd;
static std::default_random_engine engine{rd()};

class Cache{    
    public: 
        virtual ~Cache() = default;
        Cache(const int&, const int&, const int&, const int&);
      //  Cache() = default;
        void bRead(const std::size_t &);
        void bWrite(const std::size_t &);
        void bDisplaySpec() const;
        //helpers
        std::string getIndex(const std::size_t &) const;
        std::string getTag(const std::size_t & )  const;
        std::size_t getIndex_i(const std::size_t &) const;

        inline int getReadNum() const{return this->readNum;}
        inline int getWriteNum() const{return this->writeNum;}

        inline int getassoc() const{
            return this->associaticity;
        }

        inline int getNumOfEntries() const {
            return this->numOfentries;
        };

    const inline static int aBus{64}; 

    protected:
         int addressBits{32};
         int hits{0};
         int misses{0};
         int writeNum{0};
         int readNum{0};
         int  numOfentries;
         int  tagBits;
         int  indexBits;
         int  offsetBits;
         int read_misses{0};
         int read_hits{0};
         int write_misses{0};
         int write_hits{0};
        
    private: 
        int     cacheSize{0};
        int     associaticity{0} ;
        int     blockSize{0};  
        // float   hitRatio{0.0};
        // float   missRatio{0.0};

 

        virtual void displaySpec() const        =0;
        virtual void Read(const std::size_t &)  = 0;
        virtual void Write(const std::size_t &) = 0;

};