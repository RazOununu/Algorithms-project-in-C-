//vanunuraz@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "graph.hpp"
#include "queue.hpp"
#include "unionFind.hpp"
#include "Algorithms.hpp"
#include <stdexcept>
using namespace graph;

//graph
TEST_CASE("Graph: adding edge with invalid node"){
    Graph g(5);
    CHECK_THROWS_AS(g.addEdge(-1, 1, 1), std::out_of_range);
    CHECK_THROWS_AS(g.addEdge(1, 5, 1), std::out_of_range);
}

TEST_CASE("Graph: adding existing edge"){
    Graph g2(5);
    g2.addEdge(0,1,2);
    CHECK_THROWS_AS(g2.addEdge(0, 1, 2), std::runtime_error);
}

TEST_CASE("Graph: removing non-existent edge"){
    Graph g3(5);
    g3.addEdge(0,1,2);
    CHECK_THROWS_AS(g3.removeEdge(0, 2), std::runtime_error);
}
TEST_CASE("Graph: check the function checkEdge"){
    Graph g4(5);
    g4.addEdge(0,1,2);
    CHECK(g4.checkEdge(g4, 0, 1));
    CHECK_FALSE(g4.checkEdge(g4, 1, 2));
}
TEST_CASE("Graph: check the function getNumOfNodes"){
    Graph g5(5);
    CHECK(g5.getNumOfNodes()== 5);
}

//queue
TEST_CASE("Queue: negative capacity"){
    CHECK_THROWS_AS(Queue(-5), std::invalid_argument);
}

TEST_CASE("Queue: check isEmpty()"){
    Queue q(3);
    CHECK(q.isEmpty());
    q.enqueue(10);
    CHECK_FALSE(q.isEmpty());
} 

TEST_CASE("Queue: trying enqueue more than capacity"){
    Queue q2(3);
    q2.enqueue(1);
    q2.enqueue(2);
    q2.enqueue(3);
    CHECK_THROWS_AS(q2.enqueue(4), std::overflow_error);
} 

TEST_CASE("Queue: trying dequeue from empty queue"){
    Queue q3(3);
    CHECK_THROWS_AS(q3.dequeue(), std::underflow_error);
} 

TEST_CASE("Queue: check fifo"){
    Queue q4(3);
    q4.enqueue(1);
    q4.enqueue(2);
    q4.enqueue(3);
    int v= q4.dequeue();
    CHECK(v==1);
}

// //BFS
TEST_CASE("BFS: try running BFS with invalid node") {
    Graph g(5);
    CHECK_THROWS_AS(Algorithms::bfs(g, 7), std::out_of_range);
}

TEST_CASE("BFS: BFS for unconnected graphs") {
    Graph g(5);
    g.addEdge(0, 1, 1);
    g.addEdge(2, 3, 1);
    Graph bfsOrder = Algorithms::bfs(g, 0);
    CHECK(bfsOrder.checkEdge(g,0,1));
    CHECK(bfsOrder.checkEdge(g,2,3));
    CHECK_FALSE(bfsOrder.checkEdge(g,0,2));
    CHECK_FALSE(bfsOrder.checkEdge(g,0,3));
    CHECK_FALSE(bfsOrder.checkEdge(g,0,4));
    CHECK_FALSE(bfsOrder.checkEdge(g,1,2));
    CHECK_FALSE(bfsOrder.checkEdge(g,1,3));
    CHECK_FALSE(bfsOrder.checkEdge(g,1,4));
    CHECK_FALSE(bfsOrder.checkEdge(g,2,4));
    CHECK_FALSE(bfsOrder.checkEdge(g,3,4));
}

TEST_CASE("BFS: BFS for connected graph") {
    Graph g(5);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 1);
    g.addEdge(0, 3, 1);
    g.addEdge(1, 4, 1);
    Graph bfsOrder= Algorithms::bfs(g, 0);
    CHECK(bfsOrder.checkEdge(g,0,1));
    CHECK(bfsOrder.checkEdge(g,0,2));
    CHECK(bfsOrder.checkEdge(g,0,3));
    CHECK(bfsOrder.checkEdge(g,1,4));
    CHECK_FALSE(bfsOrder.checkEdge(g,0,4));
    CHECK_FALSE(bfsOrder.checkEdge(g,1,2));
    CHECK_FALSE(bfsOrder.checkEdge(g,1,3));
    CHECK_FALSE(bfsOrder.checkEdge(g,1,3));
    CHECK_FALSE(bfsOrder.checkEdge(g,1,3));
    CHECK_FALSE(bfsOrder.checkEdge(g,2,3));
    CHECK_FALSE(bfsOrder.checkEdge(g,2,4));
    CHECK_FALSE(bfsOrder.checkEdge(g,3,4));
    CHECK_FALSE(bfsOrder.checkEdge(g,3,2));
    CHECK_FALSE(bfsOrder.checkEdge(g,3,1));
}

//DFS
TEST_CASE("DFS: try running DFS with invalid node"){
    Graph g6(5);
    CHECK_THROWS_AS(Algorithms::dfs(g6, 7), std::out_of_range);
}
TEST_CASE("DFS: DFS for unconnected graphs"){
    Graph g7(5);
    g7.addEdge(0, 1, 1);
    g7.addEdge(0, 2, 1);
    g7.addEdge(3, 4, 1);
    Graph dfsOrder = Algorithms::dfs(g7, 0);
    CHECK(dfsOrder.checkEdge(g7,0,1));
    CHECK(dfsOrder.checkEdge(g7,0,2));
    CHECK(dfsOrder.checkEdge(g7,3,4));
    //recursive call on 1 not found connected node--> move to the next edge from 0
    CHECK_FALSE(dfsOrder.checkEdge(g7,1,2));
    CHECK_FALSE(dfsOrder.checkEdge(g7,1,3));
    CHECK_FALSE(dfsOrder.checkEdge(g7,1,4));
}

TEST_CASE("DFS: neighbors in DFS for connected graph"){
    Graph g8(5);
    g8.addEdge(0, 1, 1);
    g8.addEdge(0, 2, 1);
    g8.addEdge(0, 3, 1);
    g8.addEdge(1, 4, 1);
    Graph dfsOrder= Algorithms::dfs(g8, 0);
    CHECK(dfsOrder.checkEdge(g8,0,1));
    CHECK(dfsOrder.checkEdge(g8,1,4));
    CHECK(dfsOrder.checkEdge(g8,0,2));
    CHECK(dfsOrder.checkEdge(g8,0,3));
}

//Dijkstra
TEST_CASE("Dijkstra: try running with invalid node"){
    Graph g9(5);
    CHECK_THROWS_AS(Algorithms::dijkstra(g9, 7), std::out_of_range);
}

TEST_CASE("Dijkstra: negative edge by the input graph"){
    Graph g10(5);
    g10.addEdge(0, 1, -1);
    CHECK_THROWS_AS(Algorithms::dijkstra(g10, 0), std::out_of_range);
}

TEST_CASE("Dijkstra: returns minimal distances"){
    Graph g11(5);
    g11.addEdge(0, 1, 2);
    g11.addEdge(0, 2, 10);
    g11.addEdge(1, 2, 3);
    g11.addEdge(2, 3, 1);
    g11.addEdge(3, 4, 2);
    Graph dijkstraG = graph::Algorithms::dijkstra(g11, 0);
    CHECK(getDistance(dijkstraG, 0) == 0);
    CHECK(getDistance(dijkstraG, 1) == 2);
    CHECK(getDistance(dijkstraG, 2) == 5);
    CHECK(getDistance(dijkstraG, 3) == 6);
    CHECK(getDistance(dijkstraG, 4) == 8);
}

TEST_CASE("Dijkstra: unreachable nodes remain at INF distance"){
    Graph g12(5);
    g12.addEdge(0, 1, 1);
    Graph dijkstraG2=Algorithms::dijkstra(g12, 0);
    const int INF= 1e9;
    //reachable nodes
    CHECK(getDistance(dijkstraG2,0) == 0);
    CHECK(getDistance(dijkstraG2,1) == 1);
    //unreachable nodes
    CHECK(getDistance(dijkstraG2,2) == INF);
    CHECK(getDistance(dijkstraG2,3) == INF);
    CHECK(getDistance(dijkstraG2,4) == INF);
 }

TEST_CASE("Dijkstra: check relax"){
    Graph g13(4);
    g13.addEdge(0, 1, 10);
    g13.addEdge(1, 2, 10);
    g13.addEdge(2, 3, 10);
    Graph dijkstraG3=Algorithms::dijkstra(g13, 0);
    int dist = getDistance(dijkstraG3, 3);
    CHECK(dist == 30);
    //Add a new edge
    g13.addEdge(0, 3, 5);
    Graph dijkstraG4=Algorithms::dijkstra(g13, 0);
    int distNew = getDistance(dijkstraG4, 3);
    CHECK(distNew == 5);
}

//Prim
TEST_CASE("Prim: non connected graph is not valid"){
    Graph g14(5);
    g14.addEdge(0, 1, 1);
    g14.addEdge(1, 2, 2);
    g14.addEdge(3, 4, 3);
    CHECK_THROWS_AS(Algorithms::prime(g14), std::runtime_error);
}

TEST_CASE("Prim: connected graph"){
    Graph g15(4);
    g15.addEdge(0, 1, 2);
    g15.addEdge(0, 2, 1);
    g15.addEdge(1, 2, 1);
    g15.addEdge(2, 3, 4);
    Graph primOrder= Algorithms::prime(g15);
    int totalWeight= TotalWeight(primOrder);
    CHECK(totalWeight== 6);
}

//UnionFind
TEST_CASE("UnionFind: nodes not connected at start"){
    graph::UnionFind uf(5);
    for (int i = 0; i < 5; i++) {
        for (int j = i+1; j < 5; j++) {
            CHECK_FALSE(uf.connected(i, j));
        }
    }
}

TEST_CASE("UnionFind: union groups"){
    graph::UnionFind uf(5);
    uf.unionGroup(0, 1);
    uf.unionGroup(1, 2);
    CHECK(uf.connected(0, 1));
    CHECK(uf.connected(1, 2));
    CHECK(uf.connected(0, 2));
    
    CHECK_FALSE(uf.connected(0, 3));

    uf.unionGroup(3, 4);
    CHECK(uf.connected(3, 4));
}

//Kruskal
TEST_CASE("Prim: non connected graph is not valid"){
    Graph g19(5);
    g19.addEdge(0, 1, 1);
    g19.addEdge(1, 2, 2);
    g19.addEdge(3, 4, 3);
    CHECK_THROWS_AS(Algorithms::kruskal(g19), std::runtime_error);
}

TEST_CASE("Kruskal: MST has minimal total weight"){
    graph::Graph g18(4);
    g18.addEdge(0, 1, 1);
    g18.addEdge(0, 2, 4);
    g18.addEdge(1, 2, 2);
    g18.addEdge(1, 3, 3);
    g18.addEdge(2, 3, 5);
    Graph mst = Algorithms::kruskal(g18);
    int totalWeight = TotalWeight(mst);
    CHECK(totalWeight == 6);
}