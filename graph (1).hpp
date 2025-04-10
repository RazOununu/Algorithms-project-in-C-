//vanunuraz@gmail.com
#ifndef Graph_hpp
#define Graph_hpp
#include "node.hpp"
#include "edge.hpp"
namespace graph{
    class Graph{
        private:
            int numOfNodes;
            Edge** adjacencyList;//list of lists for each nodes
        public:
            Graph(int numOfNodes);
            //dynamic allocation of the adjacency list, must have a destructor, copy constructor and copy assignment operator
            ~Graph();
            Graph(const Graph& other);
            Graph& operator =(const Graph& other); 

            void addEdge(int sourceId, int destId, int wheight);
            void removeEdge(int sourceId, int destId);
            void print_graph() const; //const-->print not change the graph

            int getNumOfNodes() const; //const-->getNumOfNodes not change the graph

            //static-->not connected to the object
            static bool checkEdge (const Graph& g, int s, int d);

            //friend-->this function can access private members of the graph even if the members are private
            friend class Algorithms;
            friend void dfsVisit(const Graph& g, Graph& dfsOrder, int u, bool visited[]);
            friend int TotalWeight(const Graph& g);
            friend int getDistance(const Graph& g, int id);
    };
}    
#endif    