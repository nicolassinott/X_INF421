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

        // For Task 3 (itineraries_v2)

        vector<int> depth_mp;// Takes 1 as root and maps to the depth of element with respect to 1
        vector<vector<pair<int,int>>> ancestors_mp;

        // For Task 4 (itineraries_v3)

        UnionFind color_set;
        vector<int> color_seen;
        unordered_map<int, int> hash_weight_mp;

        Graph(int aN, int aM) {
            n = aN;
            m = aM;

            // Necessary for the generation of the MST

            mst_UF = UnionFind(aN); //getUnionFind(aN);
            mst = vector<vector<pair<int,int>>>(n);
            
            // Only necessary from Task 3

            for(int i = 0; i < n; i++) depth_mp.push_back(-1); // only for task 3
            ancestors_mp = vector<vector<pair<int,int>>>(n);

            // Only ncessary from Task 4

            color_set = UnionFind(aN);
            color_seen = vector<int>(n);
        }

        void add_edge(int v1, int v2, int w){
            vector<int> new_edge{v1,v2,w};
            edges.push_back(new_edge);
        }

        void add_edge_mst(int v1, int v2, int w){
            mst[v1].push_back({v2,w});
            mst[v2].push_back({v1,w});
        }

        void make_mst(){
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
                
                if(mst_UF.find_parent(currEdge[0]) != mst_UF.find_parent(currEdge[1])){
                    add_edge_mst(currEdge[0], currEdge[1], currEdge[2]);
                    mst_UF.union_vertices(currEdge[0], currEdge[1]);
                    count++;
                }

                idQueue++;
            }
            
            return;
        }

        int itineraries_v1(int u, int v){ 
            if(mst.empty()) make_mst();
            
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

        void tarjan_lca(int u, vector<pair<int,int>>& queries, vector<int>& output){

            for(const auto& [child, weight] : mst[u]){
                tarjan_lca(child, queries, output);
                color_set.union_vertices_color_set(u, child, depth_mp[u], depth_mp[child]);
                // add weight of child - parent as well
            }

            color_seen[u] = 1;
            ///
            for(int i = 0; i < queries.size(); i++){
                auto [x,y] = queries[i];
                if(u == x && color_seen[y]){
                    output[i] = color_set.find_parent(y); // here must perform the upward movement instead
                }

                if(u == y && color_seen[x]){
                    output[i] = color_set.find_parent(x); // here must perform the upward movement instead
                }
            }

            
        }

        // functions to allow the mapping {ancestor, node} -> weight
        int hash_function(int ancestor, int node){
            return ancestor * n + node;
        }

        pair<int,int> de_hash_function(int hash){
            int ancestor = hash % n; 
            int node = hash - ancestor * n;
            return {ancestor, node};
        }

        // updating ancestor weight mapping

        void upward_update(int node){
            if(node == color_set.find_parent(node)) return;
            return; //hash_weight_mp
        }

        // while the current LCA is not reach, move up and update the table

        int itineraries_v3(int i, vector<pair<int,int>> queries, vector<int> output){

            int max_weight = 0;

            max_weight = get_same_level(queries[i].first, output[i], max_weight).second;
            max_weight = max(max_weight, get_same_level(queries[i].second, output[i], max_weight).second);

            return max_weight;
        }

};
