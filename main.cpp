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
        input_graph.addEdge(u - 1, v - 1, w);
    }

    // Saving the queries
    cin >> l;

    for(int i = 0; i < l; i++){
        cin >> u >> v;
        queries.push_back({u - 1,v - 1});
    }

    cout << "2" << endl;
    input_graph.makeMST();

    cout << "a" << endl;
    input_graph.get_depth_map();
    cout << "aa" << endl;
    for(pair<int,int> query : queries){
        cout << input_graph.itineraries_v2(query.first, query.second) << endl;
    }
}
