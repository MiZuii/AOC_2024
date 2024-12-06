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

class Map
{
public:

    void load(std::vector<std::string> &input)
    {
        map.resize(input.size()+2);
        for( size_t i=0; i<input.size()+2; i++ ) map[i].resize(input[0].size()+2);
        cache.resize(input.size());
        for( size_t i=0; i<input.size(); i++ ) cache[i].resize(input[i].size());

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
    }

    bool solve()
    {
        bool get_looped = false;

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
                    get_looped = true;
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

        return get_looped;
    }

    std::vector<std::vector<MapObject>> map;
    std::vector<std::vector<std::array<bool, 4>>> cache;
    size_t gx = 0, gy = 0;
    GuardDirection gd = GuardDirection::N;

};

std::ostream &operator<<(std::ostream &os, Map &r)
{
    for( size_t y=0; y<r.map.size(); y++ )
    {
        for( size_t x=0; x<r.map[y].size(); x++ )
        {
            switch(r.map[y][x])
            {
            case MapObject::Edge:
                std::cout << '@';
                break;
            case MapObject::Obstacle:
                std::cout << '#';
                break;
            default:
                if(std::any_of(r.cache[y-1][x-1].begin(), r.cache[y-1][x-1].end(), [](bool val) { return val; } ))
                {
                    std::cout << 'x';
                }
                else
                {
                    std::cout << '.';
                }
            }
        }
        std::cout << std::endl;
    }
    return os;
}

int solution(std::vector<std::string> &input)
{
    Map baseMap{};
    baseMap.load(input);
    Map no_obstacle_map(baseMap);
    no_obstacle_map.solve();

    int res = 0;
    for( size_t y=1; y<=no_obstacle_map.cache.size(); y++ )
    {
        for( size_t x=1; x<=no_obstacle_map.cache[y-1].size(); x++ )
        {
            if( std::any_of(no_obstacle_map.cache[y-1][x-1].begin(), no_obstacle_map.cache[y-1][x-1].end(), [](bool val) { return val; } ) &&
                !(y == baseMap.gy && x == baseMap.gx))
            {
                Map map_copy(baseMap);
                map_copy.map[y][x] = MapObject::Obstacle;
                if( map_copy.solve() ) res++;
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
