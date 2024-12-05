#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <unordered_map>
#include <unordered_set>

int solution(std::vector<std::string> &input)
{
    std::unordered_map<int, std::unordered_set<int>> precedences;
    std::vector<std::vector<int>> updates;

    auto it = input.begin();
    for( ; it != input.end(); it++ )
    {
        if(it->empty()) break; // break for next input type
        precedences[std::stoi(it->substr(0, 2))].emplace(std::stoi(it->substr(3, 2)));
    }

    it++;
    for( ; it != input.end(); it++ )
    {
        updates.push_back({});
        auto &current_update = updates.back();
        std::stringstream ls(*it);
        std::string token;
        while( std::getline(ls, token, ',') )
        {
            current_update.push_back(std::stoi(token));
        }
    }

    int res = 0;
    for( auto update : updates )
    {
        bool valid = true;
        for( auto it=update.begin(); it!=update.end(); it++ )
        {
            for( auto sit=update.begin(); sit!=it; sit++ )
            {
                if( precedences[*it].find(*sit) != precedences[*it].end() )
                {
                    valid = false;
                    break;
                }
            }

            if(!valid) break;
        }

        if(!valid)
        {
            // reordering update
            while(true)
            {
                // check if middle is correct
                bool middle_correct = true;
                auto mi = ((int)update.size()-1)/2;
                auto mv = update[mi];
                auto &precs = precedences[mv];
                for( auto i=0; i<mi; i++)
                {
                    if(precs.find(update[i]) != precs.end())
                    {
                        // found value where mv should be before -> swap
                        std::swap(update[mi], update[i]);
                        middle_correct = false;
                        break;
                    }
                }
                if(middle_correct) {
                    for( auto i=(int)update.size()-1; i>mi; i--)
                    {
                        if(precedences[update[i]].find(mv) != precedences[update[i]].end())
                        {
                            // found value where it should be before mv
                            std::swap(update[mi], update[i]);
                            middle_correct = false;
                            break;
                        }
                    }
                }

                if(middle_correct)
                {
                    res += update[(update.size()-1)/2];
                    break;
                }
            }
        }
    }

    return res;
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
