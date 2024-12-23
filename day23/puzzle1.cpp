#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <queue>

int solution(std::vector<std::string> &input)
{
    int res = 0;
    std::unordered_map<std::string, std::vector<std::string>> graph;
    std::queue<std::string> stack;
    std::unordered_map<std::string, bool> visited;
    for( auto &l : input )
    {
        graph[l.substr(0, 2)].push_back(l.substr(3, 2));
        graph[l.substr(3, 2)].push_back(l.substr(0, 2));
    }

    for( auto [key, val] : graph )
    {
        stack.push(key);
    }

    while(!stack.empty())
    {
        auto e = stack.front();
        stack.pop();

        if(visited[e]) continue;
        visited[e] = true;

        for( size_t i=0; i<graph[e].size()-1; i++ )
        {
            if(visited[graph[e][i]]) continue;
            for( size_t j=i+1; j<graph[e].size(); j++ )
            {
                if(visited[graph[e][j]]) continue;
                auto &gei = graph[graph[e][i]];
                if( std::find(gei.begin(), gei.end(), graph[e][j]) != gei.end() )
                {
                    // cycle found
                    if( e[0] == 't' || graph[e][i][0] == 't' || graph[e][j][0] == 't' )
                    {
                        res++;
                    }
                }
            }
            stack.push(graph[e][i]);
        }
        stack.push(graph[e][graph[e].size()-1]);
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
