#include <bits/stdc++.h>

using namespace std;

class UnionFind{
    public:
        vector<int> parents, rank;
        int nElements;

        UnionFind(){};

        UnionFind(int n){
            nElements = n;
            
            for(int i = 0; i < n; i++){
                parents.push_back(i);
                rank.push_back(1);
            }
        }

        UnionFind(const UnionFind& UF){
            nElements = UF.nElements;
            for(auto n : UF.parents){
                parents.push_back(n);
            }
            for(auto n : UF.rank){
                rank.push_back(n);
            }
        }

        int get_parent(int u){
            return parents[u];
        }

        void set_parent(int u, int parent){
            parents[u] = parent;
        }

        void print(){
            cout << "This is the parent array:" << "\n";
            for(int i = 0; i < nElements; i++){
                cout << i << " : " << parents[i] << " | ";
            }

            cout << '\n';

            cout << "This is the rank array" << "\n";
            for(int i = 0; i < nElements; i++){
                cout << i << " : " << rank[i] << " | ";
            }
            cout << endl;
        }

        int find_parent(int v){
            int parent = parents[v];

            if(v == parent)
                return v;

            int newParent = find_parent(parent);
            
            parents[v] = newParent; // path compression

            return newParent;
        }

        void union_vertices(int v1, int v2){
            int parent1 = find_parent(v1);
            int parent2 = find_parent(v2);

            if (parent1 == parent2) return;//no union necessary
                
            if (rank[parent1] < rank[parent2])
                parents[parent1] = parent2;
            else if(rank[parent1] > rank[parent2])
                parents[parent2] = parent1;
            else{
                parents[parent2] = parent1;
                rank[parent1]++;
            }
        }

        void union_vertices_color_set(int v1, int v2, int depth_v1, int depth_v2){
            if (depth_v1 < depth_v2) parents[v2] = v1;
            else parents[v2] = v1;
        }
};