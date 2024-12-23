#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <queue>

int find_pivot(std::vector<int> &P, std::vector<int> &X, std::vector<std::vector<int>> &G)
{
    auto cc = [&G](const int &l, const int &r) { return G[l].size() < G[r].size(); };
    auto p = std::max_element(P.begin(), P.end(), cc);
    auto x = std::max_element(X.begin(), X.end(), cc);
    if( x == X.end() && p == P.end() ) return 0;
    if( x != X.end() && p != P.end() && (G[*x].size() > G[*p].size()) ) return *x;
    if( p != P.end() ) return *p;
    return *x;
}

inline __attribute__((__always_inline__)) bool v_in_N(int v, std::vector<int> &N)
{
    return std::find(N.begin(), N.end(), v) != N.end();
}

void born_kerbosch(std::vector<int> &&R, std::vector<int> &&P, std::vector<int> &&X, std::vector<std::vector<int>> &G, std::vector<int> &res)
{
    if( P.empty() && X.empty() )
    {
        if(R.size() > res.size())
        {
            res = R;
        }
        return;
    }

    auto pivot = find_pivot(P, X, G);
    std::vector<int> iter_copy = P;
    for( auto v : iter_copy )
    {
        if( v_in_N(v, G[pivot]) )
        {
            continue; // filter to: P - N(pivot)
        }

        std::vector<int> Rc = R;
        std::vector<int> Pc = P;
        std::vector<int> Xc = X;

        Rc.push_back(v);
        auto &Nv = G[v];
        Pc.erase(std::remove_if(Pc.begin(), Pc.end(), [&Nv](int e) { return !v_in_N(e, Nv); }), Pc.end());
        Xc.erase(std::remove_if(Xc.begin(), Xc.end(), [&Nv](int e) { return !v_in_N(e, Nv); }), Xc.end());

        born_kerbosch(std::move(Rc), std::move(Pc), std::move(Xc), G, res);

        P.erase(std::find(P.begin(), P.end(), v));
        X.push_back(v);

    }
}

std::string solution(std::vector<std::string> &input)
{
    std::vector<int> res;
    std::vector<int> P;
    std::unordered_map<std::string, int> graph;
    std::unordered_map<int, std::string> rev_graph;
    std::vector<std::vector<int>> G;
    int i = 0;

    for( auto &l : input )
    {
        auto u = l.substr(0, 2);
        auto v = l.substr(3, 2);

        if( graph.find(u) == graph.end() )
        {
            P.push_back(i);
            G.push_back({});
            graph[u] = i;
            rev_graph[i++] = u;
        }
        if( graph.find(v) == graph.end() )
        {
            P.push_back(i);
            G.push_back({});
            graph[v] = i;
            rev_graph[i++] = v;
        }

        G[graph[u]].push_back(graph[v]);
        G[graph[v]].push_back(graph[u]);
    }

    born_kerbosch({}, std::move(P), {}, G, res);

    std::vector<std::string> sres;
    std::transform(
        res.begin(),
        res.end(),
        std::back_insert_iterator(sres),
        [&rev_graph](const int v) { return rev_graph[v]; });

    std::sort(sres.begin(), sres.end());
    return std::accumulate(
        sres.begin()+1,
        sres.end(),
        sres[0],
        [](std::string acc, const std::string &r) { return acc + "," + r; });
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