#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>
#include <queue>
#include <assert.h>
#include <array>

constexpr std::array<std::pair<int, int>, 4> shifts = {{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}};
constexpr int HEIGHT = 71;
constexpr int WIDTH = 71;
constexpr int MAX_SIMULATION = 1024;

int solution(std::vector<std::string> &input)
{
    std::vector<std::pair<int, int>> memory_cords;
    for( auto &l : input )
    {
        auto it = l.find(',');
        memory_cords.push_back({
            std::stoi(l.substr(it+1, l.size()-it-1)),
            std::stoi(l.substr(0, it))});
    }

    std::vector<std::vector<bool>> visited(HEIGHT);
    for( auto &v : visited ) v.resize(WIDTH);

    for( size_t i=0; i<MAX_SIMULATION; i++ )
    {
        auto &p = memory_cords[i];
        visited[p.first][p.second] = true;
    }

    std::queue<std::pair<std::pair<int, int>, int>> queue;
    int latest_ts = 0;
    queue.push({{0, 0}, 0});

    while (!queue.empty())
    {
        auto cpr = queue.front();
        queue.pop();

        // update timestamp
        if(cpr.second != latest_ts)
        {
            latest_ts++;
            assert(cpr.second == latest_ts);
        }

        auto cp = cpr.first;

        // check end condition
        if(cp.first == HEIGHT-1 && cp.second == WIDTH-1) break;

        // check if earlier step exists
        if( visited[cp.first][cp.second] ) continue;
        visited[cp.first][cp.second] = true;

        // generate next steps
        for( auto shift : shifts )
        {
            // skip out of bounds
            std::pair<int, int> np = {cp.first + shift.first, cp.second + shift.second};
            if( np.first < 0 ||
                np.first >= HEIGHT ||
                np.second < 0 ||
                np.second >= WIDTH)
            {
                continue;
            }

            queue.push({np, latest_ts+1});
        }
    }
    
    return latest_ts;
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
