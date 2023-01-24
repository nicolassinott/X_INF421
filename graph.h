#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
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


        // For question 3

        map<int,int> depth_mp; // Takes 1 as root and maps to the depth of element with respect to 1
        map<int, vector<pair<int,int>>> ancestors_mp; // Maps each tree element to its power of two ancestors with weight 

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

        void get_depth_map(){
            queue<int> bfs;
            bfs.push(1);

            int curr_level = 0;
            int next_child_counter = 0;
            int curr_child_counter = 1;

            int curr_node;

            while(!bfs.empty()){
                curr_node = bfs.front();
                bfs.pop();

                depth_mp.insert({curr_node, curr_level});
                curr_child_counter--;

                for (auto const& [child_node, weight] : mst[curr_node]){
                    if(depth_mp.count(child_node)) continue;
                    bfs.push(child_node);
                    next_child_counter++;
                }

                if(!curr_child_counter){
                    curr_child_counter = next_child_counter;
                    next_child_counter = 0;
                    curr_level++;
                }
            }
        }

        void get_ancestors(vector<int>& parents, int level, int curr_node, int max_weight){
            vector<pair<int,int>> parent_vector;
            for(int i = 1; i < parents.size(); i * 2){
                parent_vector.push_back({parents[parents.size() - i],0});
                
            }
            ancestors_mp.insert({curr_node, parent_vector});
        }

        // void get_depth_and_ancestors_dfs(){
        //     stack<int> dfs;
        //     dfs.push(1);

        //     int curr_node;

        //     while(!dfs.empty()){
        //         curr_node = dfs.top();
        //         dfs.pop();

        //         for (auto const& [child_node, weight] : mst[curr_node]){
        //             if(depth_mp.count(child_node)) continue;
        //             dfs.push(child_node);
        //         }


                
        //     }
        // }

        void print_levels(){
            for (auto const& [key1, val1] : depth_mp){
                cout << "Node" << key1 << " has level " << val1 << endl;
                cout << "\n";
            }
        }

        int max_power2_jump(int depth_1, int depth_2){
            int power = 0;
            int dist = max(depth_1, depth_2) - min(depth_1, depth_2);

            while((1 << power) < dist){
                power++;
            }

            return power - 1; // to check
        }

        void get_same_level(int u, int v){
            int depth1 = depth_mp[u];
            int depth2 = depth_mp[v];

            //while(max_power2_jump...)
        }


};
