#include <bits/stdc++.h>
#include "UnionFind.cpp"

using namespace std;

class Graph{
    public:
        int n;
        int m;

        vector<vector<int>> edges;
        vector<vector<pair<int,int>>> mst;
        UnionFind mst_UF;

        // For question 3

        vector<int> depth_mp;// Takes 1 as root and maps to the depth of element with respect to 1
        //map<int, vector<pair<int,int>>> ancestors_mp; // Maps each tree element to its power of two ancestors with weight 

        vector<vector<pair<int,int>>> ancestors_mp;

        //Graph();

        Graph(int aN, int aM) {
            n = aN;
            m = aM;
            mst_UF = UnionFind(aN); //getUnionFind(aN);
            mst = vector<vector<pair<int,int>>>(n);
            for(int i = 0; i < n; i++){
                depth_mp.push_back(-1);
            }
            ancestors_mp = vector<vector<pair<int,int>>>(n);
        }

        void addEdge(int v1, int v2, int w){
            vector<int> new_edge{v1,v2,w};
            edges.push_back(new_edge);
        }

        void addEdgeMST(int v1, int v2, int w){
            mst[v1].push_back({v2,w});
            mst[v2].push_back({v1,w});
        }

        void makeMST(){
            // Sorting the priority queue
            sort(
                edges.begin(), 
                edges.end(), 
                [] (vector<int> v1, vector<int> v2) {
                    return v1[2] < v2[2];
                }
            );

            vector<int> currEdge;    
            int count = 0;
            int idQueue = 0;
            
            while(count < n-1){

                currEdge = edges[idQueue];
                
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
            if(mst.empty()) makeMST();
            
            vector<pair<int,int>> inverset_path(n);
            stack<int> graphStack;

            graphStack.push(u);
            int curr;

            vector<bool> seen(n);

            while(!graphStack.empty()){
                curr = graphStack.top(); graphStack.pop();

                if(curr == v) break;
                if(seen[curr]) continue; //
                
                seen[curr] = 1; //

                for (auto const& [neighbor, weight] : mst[curr]){
                    if(seen[neighbor]) continue;
                    graphStack.push(neighbor);
                    inverset_path[neighbor] = {curr, weight};
                }
            }

            int maxWeight = 0;
            int currNode = v;

            while(currNode != u){
                auto [next, weight] = inverset_path[currNode];
                maxWeight = max(maxWeight, weight); //
                currNode = next;
            }

            return maxWeight;
        }

        /// Itineraries 2

        void get_depth_map(){
            queue<int> bfs;
            bfs.push(0);

            int curr_level = 0;
            int next_child_counter = 0;
            int curr_child_counter = 1;

            int curr_node;

            while(!bfs.empty()){
                curr_node = bfs.front();
                bfs.pop();

                depth_mp[curr_node] = curr_level;
                curr_child_counter--;

                for (auto const& [child_node, weight] : mst[curr_node]){
                    if(depth_mp[child_node] != -1) continue;
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
            stack<int> dfs; dfs.push(0);
            int curr_parent = 0;
            
            vector<int> seen(n);
            seen[0] = 1;

            ancestors_mp[0].push_back({0, 0});

            while(!dfs.empty()){
                curr_parent = dfs.top(); dfs.pop();

                for (auto const& [child_node, weight] : mst[curr_parent]){
                    if(seen[child_node]) continue;
                    ancestors_mp[child_node].push_back({curr_parent, weight});
                    seen[child_node] = 1;
                    dfs.push(child_node);
                }
            }

            pair<int,int> new_ancestor;

            for(int j = 1; j < 25; j++){
                for(int v = 0; v < n; v++){
                    auto [ancestor, weight] = ancestors_mp[v][j-1];
                    new_ancestor = {ancestors_mp[ancestor][j-1].first, max(weight, ancestors_mp[ancestor][j-1].second)};
                    ancestors_mp[v].push_back(new_ancestor);
                }
            }
        }

        int max_power2_jump(int depth_1, int depth_2){
            int power = 0;
            int dist = max(depth_1, depth_2) - min(depth_1, depth_2);

            while((1 << power) <= dist){
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

            int jump = max_power2_jump(depth_u,depth_v);

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

                if(jump == 0 && ancestors_mp[u][0].first == ancestors_mp[v][0].first)
                    return max(max_weight, max(ancestors_mp[u][0].second, ancestors_mp[v][0].second));

                if(ancestors_mp[u].size() < jump || ancestors_mp[u][jump].first == ancestors_mp[v][jump].first){
                    max_weight = max(max_weight, max(ancestors_mp[u][jump-1].second, ancestors_mp[v][jump-1].second));
                    u = ancestors_mp[u][jump-1].first; v = ancestors_mp[v][jump-1].first;
                    jump = -1;
                }
            }
            return 0;
        }

        /// itineraries 3

        // vector<pair<int,int>> queries;
        // vector<int> output;

        // UnionFind color_set = UnionFind(n);

        // void tarjan_LCA(int u, unordered_set<int>& seen, vector<pair<int,int>>& queries, vector<int>& output, UnionFind& color_set){

        //     for(const auto& [child, weight] : mst[u]){
        //         tarjan_LCA(child, seen, queries, output, color_set);
        //         color_set.unionVertices(u,child);
        //         color_set.parents[color_set.findParent(u)] = u;
        //     }

        //     seen.insert(u);
        //     ///
        //     for(int i = 0; i < queries.size(); i++){
        //         auto [x,y] = queries[i];
        //         if(u == x && seen.count(y)){
        //             output[i] = color_set.findParent(y);
        //         }

        //         if(u == y && seen.count(x)){
        //             output[i] = color_set.findParent(x);
        //         }
        //     }
        // }

        // int itineraries_v3(int i, vector<pair<int,int>> queries, vector<int> output){

        //     int max_weight = 0;

        //     max_weight = get_same_level(queries[i].first, output[i], max_weight).second;
        //     max_weight = max(max_weight, get_same_level(queries[i].second, output[i], max_weight).second);

        //     return max_weight;
        // }

};
