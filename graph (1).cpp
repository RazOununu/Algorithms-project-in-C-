//vanunuraz@gmail.com
#include "graph.hpp"
#include <iostream>
#include "node.hpp"
#include "edge.hpp"
namespace graph{
    Graph::Graph(int numNodes): numOfNodes(numNodes){
        adjacencyList= new Edge*[numOfNodes];//--> delete[] adjacencyList. array of pointers to the lists of neighbors
        for (int i = 0;i<numOfNodes;i++){
            adjacencyList[i]= nullptr;
        }       
    }

    //rule of three
    Graph::~Graph(){
        //free the lists of neighbors nodes-->free the list of pointers to this lists
        for (int i=0;i<numOfNodes;i++){
            Edge* current= adjacencyList[i];//access the list of neighbors of node i
            while(current!=nullptr){
                Edge* firstToDelete= current;//temp
                current = current-> nextList;
                delete firstToDelete;
            }
        }
        delete[] adjacencyList;
    }

    Graph::Graph(const Graph& other){
        numOfNodes = other.numOfNodes;
        adjacencyList = new Edge*[numOfNodes];
        //deep copy of the adjacency list, for each node build a new list
        for(int i = 0; i < numOfNodes;++i) {
            adjacencyList[i] = nullptr;//initialize the new list
            Edge* current = other.adjacencyList[i];
            Edge** tail = &adjacencyList[i];//where to add the new edge
            //copy the list of edges of the node i
            while(current != nullptr) {
                *tail = new Edge{current->nextNode, current->wheight, nullptr};//new edge, nullptr for the next list that initialized to nullptr
                tail = &((*tail)->nextList);//pointer to the next list
                current = current->nextList;//move to the next list
            }
        }
    }

    Graph& Graph::operator=(const Graph& other){
        if(this == &other) return *this;//avoid from chaining both of them
        //free the old adjacency list of this graph
        for(int i = 0; i < numOfNodes; ++i) {
            Edge* curr = adjacencyList[i];
            while (curr != nullptr) {
                Edge* toDelete = curr;
                curr = curr->nextList;
                delete toDelete;
            }
        }
        delete[] adjacencyList;
        //now the graph empthy and i can copy the new adjacency list, deep copy
        numOfNodes = other.numOfNodes;
        adjacencyList = new Edge*[numOfNodes];
        for(int i= 0; i < numOfNodes; ++i) {
            adjacencyList[i] = nullptr;
            Edge* curr = other.adjacencyList[i];
            Edge** tail = &adjacencyList[i];
    
            while(curr != nullptr) {
                *tail = new Edge{curr->nextNode, curr->wheight, nullptr};
                tail = &((*tail)->nextList);
                curr = curr->nextList;
            }
        }
        return *this;//left object
    }

    void Graph::addEdge(int sourceId, int destId, int wheight){
        //check if the nodes in the range
        if(destId<0||destId>=numOfNodes){
            throw std::out_of_range("Invalid destId");
        }
        if(sourceId<0||sourceId>=numOfNodes){
            throw std::out_of_range("Invalid sourceId");
        }
        //check if the edge already exists
        Edge* current= adjacencyList[sourceId];
        while(current!=nullptr){
            if(current->nextNode == destId){
                throw std::runtime_error("This Edge already exists between these nodes");/////////////
                return;
            }
            current= current->nextList;
        }
        //adding first direction
        Edge* newEdge1= new Edge;
        newEdge1->wheight= wheight;
        newEdge1->nextNode= destId;
        //adding the edge to the adjacency list of sourceId
        newEdge1->nextList= adjacencyList[sourceId];
        adjacencyList[sourceId]= newEdge1;//newEdge1 is the head of the list of neighbors of sourceId
        std::cout<< "Edge added from "<< sourceId<< " to "<< destId<< std::endl;
        //adding second direction
        if(sourceId!=destId){
            Edge* newEdge2= new Edge;
            newEdge2->wheight= wheight;
            newEdge2->nextNode= sourceId;
            //adding the edge to the adjacency list of destId
            newEdge2->nextList= adjacencyList[destId];
            adjacencyList[destId]= newEdge2;//newEdge2 is the head of the list of neighbors of destId
            std::cout<< "Edge added from "<< destId<< " to "<< sourceId<< std::endl;
        }
    }

    void Graph::removeEdge(int sourceId, int destId){
        //check if the nodes in the range
        if(destId<0||destId>=numOfNodes){
            throw std::out_of_range("Invalid destId"); 
        }
        if(sourceId<0||sourceId>=numOfNodes){
            throw std::out_of_range("Invalid sourceId");
        }
        //check if the edge exists wuth the function checkEdge
        if(!checkEdge(*this, sourceId, destId)){
            throw std::runtime_error("The edge doesn't exist between sourceId and destId");
        }
        Edge* current= adjacencyList[sourceId];//--> need to delete the pointer
        Edge* prevEdge= nullptr;//not dynamic allocation
        while (current!=nullptr){
            if(current->nextNode == destId){//found the edge
                if(prevEdge== nullptr){//update in case the edge is the first in the list
                    adjacencyList[sourceId]=current->nextList;
                }
                else{
                    prevEdge->nextList= current->nextList;//update and skip the edge
                }    
                delete current;
                return;
            }
            prevEdge= current;
            current= current->nextList;
        }
        //remove the edge in the other direction
        if(!checkEdge(*this, destId, sourceId)){
            throw std::runtime_error("The edge doesn't exist between destId and sourceId");
            return;
        }
        current= adjacencyList[destId];//--> need to delete the pointer
        prevEdge= nullptr;//--> need to delete the pointer
        while(current!=nullptr){
            if(current->nextNode == sourceId){//found the edge
                if(prevEdge== nullptr){//update in case the edge is the first in the list
                    adjacencyList[destId]=current->nextList;
                }
                else{
                    prevEdge->nextList= current->nextList;//update and skip the edge
                }    
                delete current;
                return;
            }
            prevEdge= current;
            current= current->nextList;
        }
    }    

    //for each node, print the list of neighbors
    void Graph::print_graph() const{
        std::cout<< "The graph is"<< std::endl;
        for(int i=0;i<numOfNodes;i++){
            std::cout<< "Node "<<i<< ": "<< std::endl;
            Edge* current= adjacencyList[i];
            while(current!=nullptr){
                std::cout << "("<<i<< " v:" << current->nextNode<< " w:" <<current->wheight<< ") ";
                current=current->nextList;
            }
            std::cout<< "\n"<< std::endl;
        }
    }

    //check if the edge exists
    bool Graph:: checkEdge (const Graph& g, int s, int d){
        Edge* current = g.adjacencyList[s];
        while (current!=nullptr){
            if(current->nextNode == d){
                return true;
            }
            current = current->nextList;
        }
        return false;
    }

    //used to create new graph to the algorithms methods
    int Graph::getNumOfNodes() const{
        return numOfNodes;
    }  
}     