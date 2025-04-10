//vanunuraz@gmail.com
#include <iostream>
#include <stdexcept>
#include "queue.hpp"
namespace graph{
    //implemente of circular queue by array and FIFO
    Queue::Queue(int capacity){
        if(capacity <= 0){
            throw std::invalid_argument("The capacity invalid ,must be positive");
            return;
        }
        q = new int[capacity]; //--> delete
        front = 0;
        last = 0;
        count= capacity+1;
    }

    Queue::~Queue(){
        if(q!=nullptr){
            delete[] q;
            q=nullptr;
        }
    }

    bool Queue::isEmpty(){
        return (front == last); //start from 2 pointers in the beginning
    }

    //using modulus to implement circular queue
    void Queue::enqueue(int v){
        if((last+1)%count == front){
            throw std::overflow_error("The queue is full");
            return;
        }
        q[last] = v;
        last=(last+1)%count;
        std::cout<< "The value "<<v<< " was added to the queue"<<std::endl;
        return;
    }

    int Queue::dequeue(){
        if(isEmpty()){
            throw std::underflow_error("The queue is empty");
            return -1;
        }
        int v = q[front];
        front = (front + 1) % count;
        std::cout<< "The value "<<v<< " was removed from the queue"<<std::endl;
        return v;
    }
}
