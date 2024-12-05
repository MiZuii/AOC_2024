#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <unordered_map>
#include <numeric>

class WordCache
{
public:
    WordCache() = default;

    WordCache(std::array<WordCache, 4>prevs, char c)
    {
        count = prevs[0].getCount();
        for( auto i=0; i<4; i++ )
        {
            word_idx[i] = prevs[i].getWX(i) + 1 == word[c] ? word[c] : ( word[c] == 1 ? 1 : 0 );
            rev_word_idx[i] = prevs[i].getRWX(i) + 1 == rev_word[c] ? rev_word[c] : ( rev_word[c] == 1 ? 1 : 0);
        }

        for( auto i=0; i<4; i++ )
        {
            if( word_idx[i] == 4 )
            {
                word_idx[i] = 0;
                count++;
            }
            if( rev_word_idx[i] == 4 )
            {
                rev_word_idx[i] = 0;
                count++;
            }
        }
    }

    WordCache(const WordCache &other) :
        count(other.count), word_idx(other.word_idx), rev_word_idx(other.rev_word_idx)
    {}

    WordCache &operator=(const WordCache &other)
    {
        count = other.count;
        word_idx = other.word_idx;
        rev_word_idx = other.rev_word_idx;
        return *this;
    }

    int getCount() { return count; }
    int getWX(int idx) { return word_idx[idx]; }
    int getRWX(int idx) { return rev_word_idx[idx]; }

private:
    std::unordered_map<char, int> word = {{'X', 1}, {'M', 2}, {'A', 3}, {'S', 4}};
    std::unordered_map<char, int> rev_word = {{'X', 4}, {'M', 3}, {'A', 2}, {'S', 1}};

    int count = 0;

    std::array<int, 4> word_idx;
    std::array<int, 4> rev_word_idx;
};

int solution(std::vector<std::string> &input)
{
    std::unordered_map<int, std::unordered_map<int, WordCache>> cmap;
    for( int y=0; y<(int)input.size(); y++ )
    {
        for( int x=0; x<(int)input[y].size(); x++ )
        {
            cmap[x][y] = WordCache({cmap[x-1][y], cmap[x-1][y-1], cmap[x][y-1], cmap[x+1][y-1]}, input[y][x]);
        }
    }

    return std::accumulate(cmap[input.size()-1].begin(), cmap[input.size()-1].end(), 0, [&input](int acc, auto it) { return acc + it.second.getCount(); });
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
