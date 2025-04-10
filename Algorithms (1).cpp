//vanunuraz@gmail.com
#include "graph.hpp"
#include "Algorithms.hpp"
#include "queue.hpp"
#include "unionFind.hpp"
#include <stdexcept>
#include <iostream>
namespace graph{
    Graph Algorithms::bfs(const Graph& g, const int id){
        int n= g.getNumOfNodes();
        if(id>=n||id<0){
            throw std::out_of_range("Invalid start node");
            return g;
        }
        Graph bfsOrder(n);//new graph
        Queue queueBfs=(n);//new queue
        //array to keep in BFS which nodes are visited
        bool* visited = new bool[n]; //-->delete[] visited;
        for(int i=0;i<n;i++){
            visited[i]= false;
        }

        //BFS order
        //start from id
        visited[id] = true;
        queueBfs.enqueue(id);
        while(!queueBfs.isEmpty()){
            int u = queueBfs.dequeue();
            Edge* edgeOfU = g.adjacencyList[u];
            while(edgeOfU!= nullptr) {
                int nextNode = edgeOfU->nextNode;
                if(!visited[nextNode]){
                    visited[nextNode] = true;
                    bfsOrder.addEdge(u, nextNode, edgeOfU->wheight);
                    queueBfs.enqueue(nextNode);//add the neighbors of u to the queue
                }
                edgeOfU = edgeOfU->nextList;//move to the next list edges
            }
        }
        delete[] visited;
        return bfsOrder;
    }

    //secondary loop
    void Algorithms::dfsVisit(const Graph& g, Graph& dfsOrder, int u, bool visited[]){
        visited[u] = true;
        Edge* edgeOfU = g.adjacencyList[u];
        while(edgeOfU!= nullptr){ //all edges of node u
            int nextNode = edgeOfU->nextNode;
            if(!visited[nextNode]){
                dfsOrder.addEdge(u, nextNode, edgeOfU->wheight);//add the edge to the dfsOrder graph
                dfsVisit(g, dfsOrder, nextNode, visited);//recursive call for depth first search
                visited[nextNode] = true;
            }
            edgeOfU = edgeOfU->nextList;//move to the next edge (non connected to u)
        }
    }
    
    //Main loop
    Graph Algorithms::dfs(const Graph& g, const int id){
        int n= g.getNumOfNodes();
        if(id>= n||id<0){
            throw std::out_of_range("Invalid start node");
        }
    
        Graph dfsOrder(n);//new graph
        bool* visited= new bool[n];//dynamically allocate memory for visited array--> delete[] visited
        for(int i=0; i<n; i++){
            visited[i]= false;
        }
        dfsVisit(g, dfsOrder, id, visited);

        delete[] visited;
        return dfsOrder;
    }
    
    const int INF = 1e9;//infinity value--> used for unreachable nodes: minimaliNode and dijkstra, prime

    //function to find the node with the minimum distance---> used in dijkstra and prime
    static int minimaliNode(const int dist[], const bool visited[], int n){
        int minDistance = INF;
        int minimaliNode = -1;
        for(int i = 0; i < n; i++) {
            if(visited[i]==false && dist[i]< minDistance){ //if all visited return -1
                minDistance = dist[i];
                minimaliNode = i;
            }
        }
        return minimaliNode;
    }

    Graph Algorithms::dijkstra(const Graph& g, const int id){
        int n = g.getNumOfNodes();
        if(id >= n||id < 0) {
            throw std::out_of_range("Invalid start node");
        }
    
        //check if the graph has negative weights
        for(int i = 0; i < n; i++){
            Edge* edge = g.adjacencyList[i];
            while(edge != nullptr) {
                if(edge->wheight < 0){
                    throw std::out_of_range("Invalid weight, negative weight");
                }
                edge = edge->nextList;
            }
        }
    
        Graph dijkstraTree(n);//new graph
        //arrays to keep track of visited nodes, parent nodes and distances--> need to be deleted!!!
        bool* visited = new bool[n];
        int* pai = new int[n];
        int* distance = new int[n];
        for(int i = 0; i < n; i++){
            distance[i] = INF;
            visited[i] = false;
            pai[i] = -1;
        }
        distance[id] = 0;
    
        //find the shortest path- relax
        for(int i = 0; i < n; i++){
            int u = minimaliNode(distance, visited, n);
            if(u == -1) {
                break;//all nodes visited
            }
            visited[u] = true;
    
            Edge* edgeOfU = g.adjacencyList[u];
            while(edgeOfU != nullptr){
                int nextNode = edgeOfU->nextNode;
                int wheight = edgeOfU->wheight;
                if(!visited[nextNode] && distance[u] + wheight < distance[nextNode]){
                    distance[nextNode] = distance[u] + wheight;//update just the distance array
                    pai[nextNode] = u;
                }
                edgeOfU = edgeOfU->nextList;
            }
        }
    
        //build the Dijkstra tree with the updated distances
        for(int i = 0; i < n; i++){
            if(pai[i] != -1) {
                Edge* edgeOfFather = g.adjacencyList[pai[i]];
                while(edgeOfFather != nullptr) {
                    if(edgeOfFather->nextNode == i){
                        dijkstraTree.addEdge(pai[i], i, edgeOfFather->wheight);
                        break;
                    }
                    edgeOfFather = edgeOfFather->nextList;
                }
            }
        }

        //clean memory
        delete[] visited;
        delete[] pai;
        delete[] distance;
        return dijkstraTree;
    }

//not efficient, i have to keep all the prosses again because i need the original graph
int getDistance(const Graph& g, int id){
    int n = g.getNumOfNodes();
    if(id >= n || id < 0){
        throw std::out_of_range("Invalid node");
    }

    int* distance = new int[n];//--> delete[] distance;
    bool* visited = new bool[n];//--> delete[] visited;
    for(int i = 0; i < n;i++){
        distance[i] = INF;
        visited[i] = false;
    }
    distance[0] = 0;

    for(int i = 0;i < n;i++){
        int u = -1;
        for(int j = 0; j< n; j++) {//find the node with the minimum distance
            if(!visited[j] && (u == -1 || distance[j] < distance[u])){
                u = j;
            }
        }
        if(u == -1 || distance[u] == INF)
            break;//all reachable nodes are visited
        visited[u] = true;

        //relax
        Edge* edge = g.adjacencyList[u];
        while(edge != nullptr) {
            int v = edge->nextNode;
            int weight = edge->wheight;
            if (!visited[v] && distance[u] + weight < distance[v]){
                distance[v] = distance[u] + weight;
            }
            edge = edge->nextList;
        }
    }

    int result = distance[id];
    delete[] distance;
    delete[] visited;

    return result;
}

    Graph Algorithms::prime(const Graph& g){
        int n = g.getNumOfNodes();
        Graph minTPrime(n);//new graph
        bool inMST[n];//-->dynamically allocate memory
        int parentInMinPath[n];//-->dynamically allocate memory
        int minWheight[n];//dynamically allocate memory
        for(int i = 0; i < n; i++){
            inMST[i] = false;
            minWheight[i] = INF;
            parentInMinPath[i] = -1;
        }
        minWheight[0] = 0;//start from node 0
        //find the minimum weight edge
        for (int i = 0; i < n; i++) {
            int u = minimaliNode(minWheight, inMST, n);
            if(u == -1)
                throw std::runtime_error("Graph is not connected, not all nodes are reachable");
            
            //add edge to MST
            inMST[u] = true;
            if(parentInMinPath[u] != -1){
                minTPrime.addEdge(parentInMinPath[u], u, minWheight[u]);
            }
            //update weights and parents for adjacent nodes
            Edge* edgeOfU = g.adjacencyList[u];
            while(edgeOfU != nullptr){
                int nextNode = edgeOfU->nextNode;
                int wheight = edgeOfU->wheight;
                if(!inMST[nextNode] && wheight < minWheight[nextNode]){
                    minWheight[nextNode] = wheight;
                    parentInMinPath[nextNode] = u;
                }
                edgeOfU = edgeOfU->nextList;
            }
        }
        return minTPrime;
    }

    //for tests of MST
    int TotalWeight(const Graph& g){
        int total= 0;
        int n= g.getNumOfNodes();
        for(int i = 0; i < n; i++){
            graph::Edge* current = g.adjacencyList[i];
            while(current != nullptr){
                total+= current->wheight;
                current= current->nextList;
            }
        }
        return total/2;//each edge is counted twice 
    }

    Graph Algorithms::kruskal(const Graph& g){
        int n = g.getNumOfNodes();
        Graph minKruskal(n); // New graph for MST
        UnionFind myU(n);
    
        // Count edges without duplicates
        int CountEdge = 0;
        for(int i = 0;i < n; i++){
            Edge* edgeOfU = g.adjacencyList[i];
            while (edgeOfU != nullptr){
                if(i < edgeOfU->nextNode){ // Count each edge only once
                    CountEdge++;
                }
                edgeOfU = edgeOfU->nextList;
            }
        }
    
        //i use it just here to avoid duplicates
        struct EdgeWithStart{
            int startNode;
            Edge edge;
        };
    
        EdgeWithStart* edges = new EdgeWithStart[CountEdge]; //dynamically allocate memory for edges--> delete[] edges;
        int pointer = 0;
        for(int i= 0; i < n; i++){
            Edge* edgeOfU = g.adjacencyList[i];
            while(edgeOfU != nullptr){
                if(i < edgeOfU->nextNode){ //avoid duplicates
                    edges[pointer++] = {i, *edgeOfU};
                }
                edgeOfU = edgeOfU->nextList;
            }
        }
    
        //sort edges by weight
        for(int i = 0; i < CountEdge - 1; i++){
            int minIndex = i;
            for(int j = i + 1; j < CountEdge; j++){
                if(edges[j].edge.wheight < edges[minIndex].edge.wheight){
                    minIndex = j;
                }
            }
            //swap
            EdgeWithStart temp = edges[i];
            edges[i] = edges[minIndex];
            edges[minIndex] = temp;//will be checked again
        }
    
        for(int i = 0; i < CountEdge; i++){
            int u = edges[i].startNode;//source node
            int v = edges[i].edge.nextNode;//dest node
            int wheight = edges[i].edge.wheight;
    
            //add edge to MST if not make circle
            if(!myU.connected(u, v)) {
                minKruskal.addEdge(u, v, wheight);
                myU.unionGroup(u, v);
            }
        }
    
        //check if the graph is connected
        for(int i = 1; i < n; i++){
            if(!myU.connected(0, i)){ //all nodes must share the same root
                delete[] edges; //free memory before out
                throw std::runtime_error("Graph is not connected, invalid MST");
            }
        }
    
        //clean up memory
        delete[] edges;
        return minKruskal;
    }

}