#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <cmath>

using stone_t = unsigned long long;
using result_t = unsigned long long;
using cache_t = std::unordered_map<stone_t, std::unordered_map<int, result_t>>;

int count_nums(stone_t x)
{
    int count = 0;
    do
    {
        count++;
    } while(x /= 10);
    return count;
}

stone_t blink(stone_t stone, int blinks_left, cache_t &cache)
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

    result_t res = 0;
    int count = 0;
    if( stone == 0 )
    {
        res = blink(1, blinks_left-1, cache);
    }
    else if( (count = count_nums(stone)) % 2 == 0 )
    {
        int div = std::pow(10, count/2);
        stone_t ldigit = stone / div;
        stone_t rdigit = stone % div;
        res = blink(ldigit, blinks_left-1, cache) + blink(rdigit, blinks_left-1, cache);
    }
    else
    {
        res = blink(stone*2024, blinks_left-1, cache);
    }

    cache[stone][blinks_left] = res;
    return res;
}

result_t solution(std::vector<std::string> &input)
{
    std::stringstream is(input[0]);
    std::string token;
    std::vector<stone_t> stones;
    cache_t cache;
    while(std::getline(is, token, ' '))
    {
        stones.push_back(std::stoull(token));
    }

    return std::accumulate(stones.begin(), stones.end(), result_t(0), [&cache](result_t &acc, stone_t &r) { return acc + blink(r, 25, cache); });
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
