#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <vector>
#include <algorithm>
#include "UnionFind.h"

using namespace std;

UnionFind getUnionFind(int aN){
    UnionFind toRet(aN);  
    return toRet;
}

class Graph{
    public:
        int n;
        int m;
        map<int, map<int,int>> edges;
        map<int, map<int,int>> mst;
        //UnionFind mst_UF;

        //Graph();

        Graph(int aN, int aM) {
            for(int i = 1; i <= aN; i++){
                edges[i] = {};
            }
            n = aN;
            m = aM;
            //mst_UF = getUnionFind(aN);
        }

        void addEdge(int v1, int v2, int w){
            edges[v1].insert({v2,w});
            edges[v2].insert({v1,w});
        }

        void addEdgeMST(int v1, int v2, int w){
            mst[v1].insert({v2,w});
            mst[v2].insert({v1,w});
        }

        void print(){
            for (auto const& [key1, val1] : edges){
                cout << key1 << ':' << endl;
                for (auto const& [key2, val2] : val1){
                    cout << "\t" << key2 << ':' << val2 << endl;
                }
                cout << "\n";
            }
        }

        void printMST(){
            for (auto const& [key1, val1] : mst){
                cout << key1 << ':' << endl;
                for (auto const& [key2, val2] : val1){
                    cout << "\t" << key2 << ':' << val2 << endl;
                }
                cout << "\n";
            }
        }

        void makeMST(){ 
        
            UnionFind mst_UF(n);

            // Generating priority queue of edges
            vector<vector<int>> priorityQueue;            

            for (auto const& [key1, val1] : edges){    
                for (auto const& [key2, val2] : val1){
                    vector<int> edge {key1, key2, val2};
                    priorityQueue.push_back(edge);
                }
            }

            // Sorting the priority queue
            sort(
                priorityQueue.begin(), 
                priorityQueue.end(), 
                [] (vector<int> v1, vector<int> v2) {
                    return v1[2] < v2[2];
                }
            );

            vector<int> currEdge;    
            int count = 0;
            int idQueue = 0;
            
            while(count < n-1){
                currEdge = priorityQueue[idQueue];
                
                if(mst_UF.findParent(currEdge[0]) != mst_UF.findParent(currEdge[1])){
                    addEdgeMST(currEdge[0], currEdge[1], currEdge[2]);
                    mst_UF.unionVertices(currEdge[0], currEdge[1]);
                    count++;
                }

                idQueue++;
            }
            
            return;
        }

        int itineraries_v1(int u, int v){ 
            if(mst.empty())
                makeMST();
            
            map<int, int> inversePath;
            stack<int> graphStack;
            set<int> seen = {};

            graphStack.push(u);

            while(!graphStack.empty()){
                int curr = graphStack.top();
                graphStack.pop();

                if(curr == v){break;}

                if(seen.find(curr) != seen.end()){continue;} //
                seen.insert(curr); //

                for (auto const& [neighbor, weight] : mst[curr]){
                    graphStack.push(neighbor);

                    if(seen.find(neighbor) == seen.end()){
                            inversePath[neighbor] = curr;
                    }
                }
            }

            int maxWeight = 0;
            int currNode = v;

            while(currNode != u){
                int next = inversePath[currNode];
                maxWeight = max(maxWeight, mst[currNode][next]); //
                currNode = next;
            }

            return maxWeight;
        }

};
