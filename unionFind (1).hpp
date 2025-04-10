//vanunuraz@gmail.com
#ifndef unionFind_hpp
#define unionFind_hpp
namespace graph{
    class UnionFind{
        private:
            int* parent;
            int* rank;
            int size;
        public:
            UnionFind(int num);
            ~UnionFind();//destructor
            bool connected(int u, int v);
            int find(int u);
            void unionGroup(int u, int v);
            
            //for kruskal i need access to the private memmory
            friend class Algorithms;
    };
}
#endif