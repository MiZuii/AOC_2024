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

void dfs(point_t p, std::vector<std::vector<std::array<bool, 4>>> &visited, const std::vector<std::vector<std::array<std::vector<point_t>, 4>>> &predecesors)
{
    visited[std::get<0>(p)][std::get<1>(p)][std::get<2>(p)] = true;
    for( auto &np : predecesors[std::get<0>(p)][std::get<1>(p)][std::get<2>(p)] )
    {
        if(!visited[std::get<0>(np)][std::get<1>(np)][std::get<2>(np)])
        {
            dfs(np, visited, predecesors);
        }
    }
}

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

    std::vector<std::vector<std::array<std::vector<point_t>, 4>>> predecesors(input.size());
    for( auto &v : predecesors )
    {
        for( size_t i=0; i<input[0].size(); i++ )
        {
            v.push_back({});
        }
    }

    q.push({0, {input.size()-2, 1, E}});
    d[input.size()-2][1][E] = 0;

    while(!q.empty())
    {
        point_t e = q.top().second;
        q.pop();
        if( input[std::get<0>(e)][std::get<1>(e)] == 'E') continue;
        if( visited[std::get<0>(e)][std::get<1>(e)][std::get<2>(e)] ) continue;
        visited[std::get<0>(e)][std::get<1>(e)][std::get<2>(e)] = true;

        {
            // rotate +1
            auto new_d = d[std::get<0>(e)][std::get<1>(e)][std::get<2>(e)] + 1000;
            auto &current_d = d[std::get<0>(e)][std::get<1>(e)][(std::get<2>(e) + 1)%4];
            auto &predecesors_v = predecesors[std::get<0>(e)][std::get<1>(e)][(std::get<2>(e) + 1)%4];

            if( new_d < current_d )
            {
                current_d = new_d;
                predecesors_v.clear();
                predecesors_v.push_back(e);

                q.push({new_d,
                       {std::get<0>(e),
                        std::get<1>(e),
                        (Direction)((std::get<2>(e) + 1)%4)}});
            }
            else if( new_d == current_d )
            {
                predecesors_v.push_back(e);
            }
        }

        {
            // rotate -1
            auto new_d = d[std::get<0>(e)][std::get<1>(e)][std::get<2>(e)] + 1000;
            auto &current_d = d[std::get<0>(e)][std::get<1>(e)][(std::get<2>(e) + 5)%4];
            auto &predecesors_v = predecesors[std::get<0>(e)][std::get<1>(e)][(std::get<2>(e) + 5)%4];

            if( new_d < current_d )
            {
                current_d = new_d;
                predecesors_v.clear();
                predecesors_v.push_back(e);

                q.push({new_d,
                       {std::get<0>(e),
                        std::get<1>(e),
                        (Direction)((std::get<2>(e) + 5)%4)}});
            }
            else if( new_d == current_d )
            {
                predecesors_v.push_back(e);
            }
        }

        if(input[std::get<0>(e)+shift(std::get<2>(e)).first][std::get<1>(e)+shift(std::get<2>(e)).second] == '.' ||
            input[std::get<0>(e)+shift(std::get<2>(e)).first][std::get<1>(e)+shift(std::get<2>(e)).second] == 'E')
        {
            // go forward
            auto new_d = d[std::get<0>(e)][std::get<1>(e)][std::get<2>(e)]+1;
            auto &current_d = d[std::get<0>(e)+shift(std::get<2>(e)).first][std::get<1>(e)+shift(std::get<2>(e)).second][std::get<2>(e)];
            auto &predecesors_v = predecesors[std::get<0>(e)+shift(std::get<2>(e)).first][std::get<1>(e)+shift(std::get<2>(e)).second][std::get<2>(e)];

            if( new_d < current_d )
            {
                current_d = new_d;
                predecesors_v.clear();
                predecesors_v.push_back(e);

                q.push({new_d,
                       {std::get<0>(e)+shift(std::get<2>(e)).first,
                        std::get<1>(e)+shift(std::get<2>(e)).second,
                        std::get<2>(e)}});
            }
            else if( new_d == current_d )
            {
                predecesors_v.push_back(e);
            }
        }
    }

    std::vector<std::vector<std::array<bool, 4>>> pv(input.size());
    for( auto &v : pv )
    {
        for( size_t i=0; i<input[0].size(); i++ )
        {
            v.push_back({false, false, false, false});
        }
    }

    // backtrack path according to best result
    if(d[1][input[0].size()-2][N] == d[1][input[0].size()-2][E])
    {
        dfs({1, input[0].size()-2, N}, pv, predecesors);
        dfs({1, input[0].size()-2, E}, pv, predecesors);
    }
    else if( d[1][input[0].size()-2][N] < d[1][input[0].size()-2][E] )
    {
        dfs({1, input[0].size()-2, N}, pv, predecesors);
    }
    else
    {
        dfs({1, input[0].size()-2, E}, pv, predecesors);
    }
    
    int res=0;
    for( auto &v : pv )
    {
        for( auto &sv : v )
        {
            if( sv[0] || sv[1] || sv[2] || sv[3] )
            {
                res++;
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
