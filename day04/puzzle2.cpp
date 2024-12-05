#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <unordered_map>
#include <numeric>

class Word
{
public:
    Word() = default;

    Word(std::array<Word, 4> chars, char nc)
    {
        count = chars[3].getCount();
        c = nc;

        if( chars[2].getChar() == 'A' )
        {
            for( int i=0; i<4; i++ )
            {
                if( word[i % 4] == chars[0].getChar() &&
                    word[(i+1) % 4] == chars[1].getChar() &&
                    word[(i+2) % 4] == nc &&
                    word[(i+3) % 4] == chars[3].getChar() )
                {
                    count++;
                    break;
                }
            }
        }
    }

    Word(const Word &other) :
        count(other.count), c(other.c)
    {}

    Word &operator=(const Word &other)
    {
        count = other.count;
        c = other.c;
        return *this;
    }

    int getCount() { return count; }
    char getChar() { return c; }

private:
    std::vector<char> word = {'M', 'M', 'S', 'S'};

    int count = 0;
    char c = '.';
};

int solution(std::vector<std::string> &input)
{
    std::unordered_map<int, std::unordered_map<int, Word>> cmap;
    for( int y=0; y<(int)input.size(); y++ )
    {
        for( int x=0; x<(int)input[y].size(); x++ )
        {
            auto w = Word({cmap[x-2][y-2], cmap[x][y-2], cmap[x-1][y-1], cmap[x-2][y]}, input[y][x]);
            cmap[x][y] = w;
        }
    }

    return std::accumulate(cmap[input.size()-1].begin(), cmap[input.size()-1].end(), 0, [&input](int acc, auto it) { return acc + it.second.getCount(); }) +
           std::accumulate(cmap[input.size()-2].begin(), cmap[input.size()-2].end(), 0, [&input](int acc, auto it) { return acc + it.second.getCount(); });
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
