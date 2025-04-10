//vanunuraz@gmail.com
#ifndef edge_hpp
#define edge_hpp
namespace graph{
    struct Edge{
        int wheight;
        int nextNode; //the destination node
        Edge* nextList;//the next list edge in the adjacency list
    };   
}
#endif