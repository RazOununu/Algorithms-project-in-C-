//vanunuraz@gmail.com
#include <iostream>
#include <stdexcept>
#include "unionFind.hpp"

namespace graph{
    UnionFind::UnionFind(int num):size(num){
        if(num <= 0){
            throw std::invalid_argument("The num invalid ,must be positive");
            return;
        }
        parent = new int[num];//-->delete[] parent
        rank = new int[num];//-->delete[] rank
        for (int i = 0; i < num; i++){
            parent[i] = i;
            rank[i] = 0; 
        }
    }
    UnionFind::~UnionFind(){
        delete[] parent;
        delete[] rank;
    }

    bool UnionFind::connected(int u, int v){
        return find(u)== find(v);
    }

    //this function find the root of u  of his group
    int UnionFind::find(int u){
        if (parent[u] != u) {
            parent[u] = find(parent[u]);//i use the way that root of u will kepp to the nex time
        }
        return parent[u];//u is the one of group
    }
    
    //union 2 group
    void UnionFind::unionGroup(int u, int v){
        int rootOfU = find(u);
        int rootOfV = find(v);
        if (rootOfU == rootOfV){
            return;
        }
        if (rootOfU != rootOfV) {//belong to different group
            if (rank[rootOfU] < rank[rootOfV]){
                parent[rootOfU] = rootOfV;
            }
            else if (rank[rootOfU] > rank[rootOfV]){
                parent[rootOfV] = rootOfU;
            }
            else{
                parent[rootOfV] = rootOfU;
                rank[rootOfU]++;
            }
        }
    }
}    