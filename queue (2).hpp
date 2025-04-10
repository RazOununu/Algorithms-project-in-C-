//vanunuraz@gmail.com
#ifndef queue_hpp
#define queue_hpp
namespace graph{
    class Queue{
        private:
            int *q;
            int front;
            int last;
            int count;
        public:
            Queue(int num);
            ~Queue(); //destructor
            bool isEmpty();
            void enqueue(int u);
            int dequeue();
    };
}
#endif