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
            cerr << "i am dumb" << endl;
            nElements = UF.nElements;
            for(auto n : UF.parents){
                parents.push_back(n);
            }
            for(auto n : UF.rank){
                rank.push_back(n);
            }
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

        int findParent(int v){
            int parent = parents[v];

            if(v == parent)
                return v;

            int newParent = findParent(parent);
            
            parents[v] = newParent; // path compression

            return newParent;
        }

        void unionVertices(int v1, int v2){
            int parent1 = findParent(v1);
            int parent2 = findParent(v2);

            if (parent1 == parent2) //no union necessary
                return;

            if (rank[parent1] < rank[parent2])
                parents[parent1] = parent2;
            else if(rank[parent1] > rank[parent2])
                parents[parent2] = parent1;
            else{
                parents[parent2] = parent1;
                rank[parent1]++;
            }
        }
};