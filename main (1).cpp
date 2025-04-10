//vanunuraz@gmail.com
#include "graph.hpp"
#include "queue.hpp"
#include "Algorithms.hpp"
#include "unionFind.hpp"
#include <iostream>
using namespace graph;
int main(){
    //graph
    std::cout<< "Running the graph<<std::endl";
    graph:: Graph simuG(4);
    simuG.addEdge(0,1,1);
    simuG.addEdge(0,2,1);
    simuG.addEdge(1,2,1);
    simuG.addEdge(2,3,1);
    simuG.print_graph();
    simuG.removeEdge(0,1);
    simuG.print_graph();
    std::cout<< "\n";

    //queue
    std::cout<< "Running the queue<<std::endl";
    Queue q(3);
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    int v= q.dequeue();
    std::cout<< "The dequeue value is: "<< v << std::endl;
    std::cout<< "\n";

    //BFS
    std::cout<< "Running the BFS<<std::endl";
    Graph simuG2(4);
    simuG2.addEdge(0,1,1);
    simuG2.addEdge(0,2,1);
    simuG2.addEdge(1,2,1);
    simuG2.addEdge(2,3,1);
    simuG2.print_graph();
    graph::Graph bfsOrder= graph::Algorithms::bfs(simuG2, 0);
    bfsOrder.print_graph();
    std::cout<< "\n";

    //DFS
    std::cout<< "Running the DFS<<std::endl";
    graph:: Graph simuG3(4);
    simuG3.addEdge(0,1,1);
    simuG3.addEdge(0,2,1);
    simuG3.addEdge(1,2,1);
    simuG3.addEdge(2,3,1);
    simuG3.print_graph();
    graph::Graph dfsOrder= graph::Algorithms::dfs(simuG3, 0);
    dfsOrder.print_graph();
    std::cout<< "\n";

    //Dijkstra
    std::cout<< "Running the Dijkstra<<std::endl";
    Graph simuG4(4);
    simuG4.addEdge(0,1,2);
    simuG4.addEdge(0,2,1);
    simuG4.addEdge(1,2,1);
    simuG4.addEdge(2,3,4);
    simuG4.print_graph();
    Graph gDIJKSTRA= graph::Algorithms::dijkstra(simuG4, 0);
    gDIJKSTRA.print_graph();
    std::cout<< "\n";

    //Prim
    std::cout<< "Running the Prim<<std::endl";
    graph:: Graph simuG5(5);
    simuG5.addEdge(0,1,2);
    simuG5.addEdge(0,2,1);
    simuG5.addEdge(1,2,1);
    simuG5.addEdge(2,3,4);
    simuG5.addEdge(3,4,2);
    simuG5.addEdge(4,0,3);
    simuG5.print_graph();
    Graph minPrim= Algorithms::prime(simuG3);
    minPrim.print_graph();
    std::cout<< "\n";

    //UnionFind
    std::cout<< "Running the UnionFind<<std::endl";
    graph::UnionFind uf(5);
    uf.unionGroup(0, 1);
    uf.unionGroup(1, 2);
    uf.unionGroup(3, 4);
    std::cout<< "\n";

    //Kruskal
    graph:: Graph simuG6(5);
    simuG6.addEdge(0,1,2);
    simuG6.addEdge(0,2,1);
    simuG6.addEdge(1,2,1);
    simuG6.addEdge(2,3,4);
    simuG6.addEdge(3,4,2);
    simuG6.addEdge(4,0,3);
    simuG6.print_graph();
    Graph minKruskal= Algorithms::kruskal(simuG6);  
    minKruskal.print_graph();

return 0;
 }

