#include <bits/stdc++.h>
#include "Graph.cpp"
//#include <fstream>

using namespace std;

int main(){

    // Set here the itineraries version you want to use {1,2,3}
    int version = 2;

    // Common Initialization //

    int n, m;
    int u, v, w;
    int l;
    vector<pair<int,int>> queries;

    // Generating graph
    cin >> n >> m;

    Graph input_graph = Graph(n, m, version);

    if(m == n - 1){
        for(int i = 0; i < m; i++){       
            cin >> u >> v >> w;
            input_graph.add_edge_mst(u - 1, v - 1, w);
        }
    } else {
        for(int i = 0; i < m; i++){       
            cin >> u >> v >> w;
            input_graph.add_edge(u - 1, v - 1, w);
        }
    }    

    // Saving the queries
    cin >> l;

    for(int i = 0; i < l; i++){
        cin >> u >> v;
        queries.push_back({u - 1,v - 1});
    }

    input_graph.make_mst();

    // ------------------- //

    // itineraries_v1 main //

    if(version == 1){
        for(pair<int,int> query : queries){
            cout << input_graph.itineraries_v1(query.first, query.second) << endl;
        }
    }

    // ------------------- //

    // itineraries_v2 main //

    if(version == 2){
        input_graph.get_depth_map();
        input_graph.get_ancestors();
        for(pair<int,int> query : queries){
            cout << input_graph.itineraries_v2(query.first, query.second) << endl;
        }
    }

    // ------------------- //

    // itineraries_v3 main //

    if(version == 3){
        vector<int> output(l);
        vector<vector<pair<int,int>>> queries_map = input_graph.get_queries_map(queries);
        input_graph.itineraries_v3(queries_map, output);
    }

    // ------------------- //
}
