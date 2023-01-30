#include <bits/stdc++.h>
#include "Graph.cpp"
//#include <fstream>

using namespace std;

int main(){
    int n, m;
    int u, v, w;
    int l;
    vector<pair<int,int>> queries;

    // Generating graph
    cin >> n >> m;

    Graph input_graph = Graph(n,m);

    for(int i = 0; i < m; i++){       
        cin >> u >> v >> w;
        input_graph.add_edge(u - 1, v - 1, w);
    }

    // Saving the queries
    cin >> l;

    for(int i = 0; i < l; i++){
        cin >> u >> v;
        queries.push_back({u - 1,v - 1});
    }

    input_graph.make_mst();

    //necessary for itinerariesv2
    input_graph.get_depth_map();
    // input_graph.get_ancestors();
    // //necessary for itinerariesv2

    // for(pair<int,int> query : queries){
    //     cout << input_graph.itineraries_v2(query.first, query.second) << endl;
    // }

    //necessary for itinerariesv3

    vector<int> output(l);
    vector<vector<pair<int,int>>> queries_map = input_graph.get_queries_map(queries);

    input_graph.itineraries_v3(queries_map, output);
}
