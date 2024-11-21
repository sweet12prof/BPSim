#pragma once
#include <print>
#include <Cache.hpp>
#include <vector>
#include <bitset>
#include <cacheline.hpp>
#include <string>
#include <memory>
class DirectMapped : public Cache{
    public:  
      DirectMapped(const int&, const int&, const int&, const int&);
      void displaySpec() const override;
    private: 
        std::vector<cacheline> line;
        void Read(const std::size_t &) override;
        void Write(const std::size_t &) override;
};