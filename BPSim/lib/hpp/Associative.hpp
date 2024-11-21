#pragma once
#include <Cache.hpp>
#include <cacheline.hpp>
#include <vector>
#include <ReplacementPolicy.hpp>
class Associative : public Cache{
    public:
        Associative(const int&, const int&, const int&, const int&);
        void displaySpec() const override;
    //helpers
        inline std::size_t getFlatIndex() const {
            return this->flatIndex;
        }

        void InitialiseReplacementPolicy(std::unique_ptr<ReplacementPolicy> );

    private:
        void Read(const std::size_t &) override;
        void Write(const std::size_t &) override;
        std::vector<cacheline> line;
        std::size_t flatIndex{0};
        std::unique_ptr<ReplacementPolicy> ReplacePolicy;
};