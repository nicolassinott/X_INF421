#include <bits/stdc++.h>
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

        void get_ancestors(){
            stack<int> dfs; dfs.push(1);
            int curr_parent = 1;
            
            unordered_set<int> seen;
            seen.insert(1);

            vector<pair<int,int>> ancestor_vector;
            
            while(!dfs.empty()){
                curr_parent = dfs.top(); dfs.pop();
                cout << curr_parent << endl;

                for (auto const& [child_node, weight] : mst[curr_parent]){
                    if(seen.count(child_node)) continue;

                    ancestor_vector.push_back({curr_parent, weight});
                    ancestors_mp.insert({child_node, ancestor_vector});
                    ancestor_vector.clear();

                    seen.insert(child_node);
                    dfs.push(child_node);
                }
            }

            print_ancestors();

            int log_2_n = max_power2_jump(n,0) + 1;
            cout << log_2_n << endl;
            pair<int,int> new_ancestor;

            for(int j = 1; j < log_2_n; j++){
                for(int v = 2; v <= n; v++){
                    if(ancestors_mp[v].size() < j-1) continue;
                    auto [ancestor, weight] = ancestors_mp[v][j-1];

                    if(ancestor == 1 || ancestors_mp[ancestor].size() < j-1) continue;
                    new_ancestor = {ancestors_mp[ancestor][j-1].first, max(weight, ancestors_mp[ancestor][j-1].second)};

                    ancestors_mp[v].push_back(new_ancestor);
                }
            }
        }

        void print_ancestors(){
            for (auto const& [node, ancestors_vector] : ancestors_mp){
                cout << "Node " << node << ":" << endl;
                cout << "\t"; 
                for(auto const& [ancestor, weight] : ancestors_vector){
                    cout << "{" << ancestor << ", " << weight << "} | "; 
                }
                cout << "\n";
            }
        }

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

            return power - 1; 
        }
        
        pair<int,int> get_same_level(int u, int v, int weight){
            // input must be so that depth(u) > depth(v)
            // returns the 

            int depth_u = depth_mp[u];
            int depth_v = depth_mp[v];

            if(depth_u == depth_v) return {u, weight};

            int jump = max_power2_jump(u,v);
            weight = max(weight, ancestors_mp[u][jump].second); // u ou v

            return get_same_level(ancestors_mp[u][jump].first, v, weight); // u ou v
        }

        int itineraries_v2(int u, int v){
            int depth_u = depth_mp[u];
            int depth_v = depth_mp[v];
            
            if(depth_v > depth_u){
                u = u + v; v = u - v; u = u - v;
            }

            int max_weight = 0;
            pair<int,int> same_level = get_same_level(u,v,max_weight);
            u = same_level.first ; max_weight = same_level.second; 

            if(u == v) return max_weight;

            int jump = -1;

            while(1){
                jump++;

                if(jump == 0 && ancestors_mp[u][jump].first == ancestors_mp[v][jump].first)
                    return max(max_weight, max(ancestors_mp[u][jump].second, ancestors_mp[v][jump].second));

                if(ancestors_mp[u][jump].first == ancestors_mp[v][jump].first){
                    max_weight = max(max_weight, max(ancestors_mp[u][jump-1].second, ancestors_mp[v][jump-1].second));
                    u = ancestors_mp[u][jump-1].first; v = ancestors_mp[v][jump-1].first;
                    jump = -1;
                }
            }
            return 0;
        }

};
