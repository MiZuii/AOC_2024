#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <cmath>
#include <gmpxx.h>

struct mpz_hash {
    std::size_t operator()(const mpz_class& z) const {
        return std::hash<std::string>()(z.get_str());
    }
};

struct mpz_equal {
    bool operator()(const mpz_class& a, const mpz_class& b) const {
        return a == b;
    }
};

mpz_class blink(mpz_class stone, int blinks_left, std::unordered_map<mpz_class, std::unordered_map<int, mpz_class>, mpz_hash, mpz_equal> &cache)
{
    if( blinks_left == 0 ) return 1;

    if( cache.find(stone) != cache.end() )
    {
        auto &sub_cache = cache[stone];
        if( sub_cache.find(blinks_left) != sub_cache.end() )
        {
            return sub_cache[blinks_left];
        }
    }

    mpz_class res = 0;
    if( stone == 0 )
    {
        res = blink(1, blinks_left-1, cache);
    }
    else if( stone.get_str().size() % 2 == 0)
    {
        mpz_class div = std::pow(10, stone.get_str().size()/2);
        mpz_class ldigit = stone / div;
        mpz_class rdigit = stone % div;
        res += blink(ldigit, blinks_left-1, cache);
        res += blink(rdigit, blinks_left-1, cache);
    }
    else
    {
        res = blink(stone*2024, blinks_left-1, cache);
    }

    cache[stone][blinks_left] = res;
    return res;
}

mpz_class solution(std::vector<std::string> &input)
{
    std::stringstream is(input[0]);
    std::string token;
    std::vector<mpz_class> stones;
    std::unordered_map<mpz_class, std::unordered_map<int, mpz_class>, mpz_hash, mpz_equal> cache;
    while(std::getline(is, token, ' '))
    {
        stones.push_back(mpz_class(token));
    }

    return std::accumulate(stones.begin(), stones.end(), mpz_class(0), [&cache](mpz_class &acc, mpz_class &r) { return acc + blink(r, 74, cache); });
}

int main(int argc, char* argv[]) {
    std::string inputFilename = "input.txt";

    std::ifstream inputFile(inputFilename);
    if (!inputFile) {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }

    std::vector<std::string> input;
    std::string line;
    while (std::getline(inputFile, line)) {
        input.push_back(line);
    }
    inputFile.close();

    std::cout << solution(input) << std::endl;
    return 0;
}
