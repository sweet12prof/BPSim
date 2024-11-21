#pragma once
#include <Cache.hpp>
#include <cacheline.hpp>
#include <bitset>

class DirectMappedNoTag : public Cache {
    public: 
        DirectMappedNoTag(const int&, const int&, const int&, const int&);
        void displaySpec() const override;
        void ValidateAllEntries();
    private:
        std::vector<cacheline> line;
        void Read(const std::size_t &) override;
        void Write(const std::size_t &) override;
};