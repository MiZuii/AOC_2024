#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>

enum class MapObject
{
    Edge,
    Obstacle,
    Empty
};

enum GuardDirection
{
    N,
    E,
    S,
    W    
};

std::pair<int, int> next_step(GuardDirection gd) // [y, x]
{
    switch(gd)
    {
    case GuardDirection::N:
        return {-1, 0};
    case GuardDirection::E:
        return {0, 1};
    case GuardDirection::S:
        return {1, 0};
    case GuardDirection::W:
        return {0, -1};
    }
    return {0, 0};
}

GuardDirection next_direction(GuardDirection gd)
{
    return static_cast<GuardDirection>(((int)gd + 1) % 4);
}

int solution(std::vector<std::string> &input)
{
    std::vector<std::vector<MapObject>> map;
    std::vector<std::vector<std::array<bool, 4>>> cache;
    map.resize(input.size()+2);
    for( size_t i=0; i<input.size()+2; i++ ) map[i].resize(input[0].size()+2);
    cache.resize(input.size());
    for( size_t i=0; i<input.size(); i++ ) cache[i].resize(input[i].size());

    size_t gx=0, gy=0;
    GuardDirection gd = GuardDirection::N;
    for( size_t y=0; y<input.size(); y++ )
    {
        for( size_t x=0; x<input[y].size(); x++ )
        {
            switch(input[y][x])
            {
            case '.':
                map[y+1][x+1] = MapObject::Empty;
                break;
            case '#':
                map[y+1][x+1] = MapObject::Obstacle;
                break;
            default:
                map[y+1][x+1] = MapObject::Empty;
                gy = y+1;
                gx = x+1;
            }
        }
    }

    cache[gy-1][gx-1][(int)gd] = true;

    while(true)
    {
        // next step cords
        auto nss = next_step(gd);
        auto ns_y = gy + nss.first;
        auto ns_x = gx + nss.second;

        if(map[ns_y][ns_x] == MapObject::Obstacle)
        {
            // perform rotation
            gd = next_direction(gd);
            cache[gy-1][gx-1][(int)gd] = true;
        }
        else if(map[ns_y][ns_x] == MapObject::Empty)
        {
            if(cache[ns_y-1][ns_x-1][(int)gd])
            {
                // cycle found
                break;
            }

            gy = ns_y;
            gx = ns_x;
            cache[gy-1][gx-1][(int)gd] = true;
        }
        else
        {
            break;
        }
    }

    int res = 0;
    for(auto cacher : cache)
    {
        for(auto v : cacher)
        {
            if( std::any_of(v.begin(), v.end(), [](bool val) { return val; } )) res++;
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
