//vanunuraz@gmail.com
#ifndef Algorithms_hpp
#define Algorithms_hpp
namespace graph{
    class Algorithms{
    public:
        Algorithms(){};//default constructor
        static Graph bfs(const Graph& g, const int id);
        static Graph dfs(const Graph& g, const int id);
        static void dfsVisit(const Graph& g, Graph& dfsOrder, int u, bool visited[]);
        static Graph dijkstra(const Graph& g, const int id);
        static Graph prime(const Graph& g);
        static Graph kruskal(const Graph& g);
    };
}
#endif    