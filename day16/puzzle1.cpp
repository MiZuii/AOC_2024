#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>
#include <queue>

enum Direction
{
    N = 0,
    E,
    S,
    W
};

using point_t = std::tuple<int, int, Direction>;
using queue_t = std::pair<int, point_t>;

std::pair<int, int> shift(Direction dir)
{
    switch (dir)
    {
    case N:
        return {-1, 0};
    case E:
        return {0, 1};
    case S:
        return {1, 0};
    case W:
        return {0, -1};
    default:
        break;
    }
    return {0, 0};
}

struct
{
    bool operator()(const queue_t &l, const queue_t &r) const
    {
        return l.first > r.first;
    }
} min_queue_ordering;

int solution(std::vector<std::string> &input)
{
    std::priority_queue<queue_t, std::vector<queue_t>, decltype(min_queue_ordering)> q(min_queue_ordering);
    std::vector<std::vector<std::array<int, 4>>> d(input.size());
    for( auto &v : d )
    {
        for( size_t i=0; i<input[0].size(); i++ )
        {
            v.push_back({__INT_MAX__, __INT_MAX__, __INT_MAX__, __INT_MAX__});
        }
    }

    std::vector<std::vector<std::array<bool, 4>>> visited(input.size());
    for( auto &v : visited )
    {
        for( size_t i=0; i<input[0].size(); i++ )
        {
            v.push_back({false, false, false, false});
        }
    }

    q.push({0, {input.size()-2, 1, E}});
    d[input.size()-2][1][E] = 0;
    visited[input.size()-2][1][E] = true;

    while(!q.empty())
    {
        point_t e = q.top().second;
        q.pop();

        if(!visited[std::get<0>(e)][std::get<1>(e)][(std::get<2>(e) + 1)%4])
        {
            // rotate +1
            d[std::get<0>(e)][std::get<1>(e)][(std::get<2>(e) + 1)%4] = d[std::get<0>(e)][std::get<1>(e)][std::get<2>(e)]+1000;
            q.push({
                d[std::get<0>(e)][std::get<1>(e)][std::get<2>(e)]+1000,
                    {std::get<0>(e),
                     std::get<1>(e),
                     (Direction)((std::get<2>(e) + 1)%4)}});
            visited[std::get<0>(e)][std::get<1>(e)][(std::get<2>(e)+1)%4] = true;
        }

        auto nd = (std::get<2>(e) - 1)%4;
        if( nd < 0 ) nd = 4+nd;

        if(!visited[std::get<0>(e)][std::get<1>(e)][nd])
        {
            // rotate -1
            d[std::get<0>(e)][std::get<1>(e)][nd] = d[std::get<0>(e)][std::get<1>(e)][std::get<2>(e)]+1000;
            q.push({
                d[std::get<0>(e)][std::get<1>(e)][std::get<2>(e)]+1000,
                    {std::get<0>(e),
                     std::get<1>(e),
                     (Direction)nd}});
            visited[std::get<0>(e)][std::get<1>(e)][nd] = true;
        }

        if(input[std::get<0>(e)+shift(std::get<2>(e)).first][std::get<1>(e)+shift(std::get<2>(e)).second] == '.' &&
           !visited[std::get<0>(e)+shift(std::get<2>(e)).first][std::get<1>(e)+shift(std::get<2>(e)).second][std::get<2>(e)])
        {
            // go forward
            d[std::get<0>(e)+shift(std::get<2>(e)).first][std::get<1>(e)+shift(std::get<2>(e)).second][std::get<2>(e)] =
                d[std::get<0>(e)][std::get<1>(e)][std::get<2>(e)]+1;
            q.push({
                d[std::get<0>(e)][std::get<1>(e)][std::get<2>(e)]+1,
                    {std::get<0>(e)+shift(std::get<2>(e)).first,
                     std::get<1>(e)+shift(std::get<2>(e)).second,
                     std::get<2>(e)}});
            visited[std::get<0>(e)+shift(std::get<2>(e)).first][std::get<1>(e)+shift(std::get<2>(e)).second][std::get<2>(e)] = true;
        }

        if(input[std::get<0>(e)+shift(std::get<2>(e)).first][std::get<1>(e)+shift(std::get<2>(e)).second] == 'E')
        {
            return d[std::get<0>(e)][std::get<1>(e)][std::get<2>(e)]+1;
        }
    }

    return 0;
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
