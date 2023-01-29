#include <bits/stdc++.h>
#include "Graph.cpp"
//#include <fstream>

using namespace std;

pair<Graph, vector<pair<int,int>>> get_input(){
    int n, m;
    int u, v, w;
    int l;
    vector<pair<int,int>> queries;


    // Generating graph
    cin >> n >> m;

    for(int i = 0; i < 10; i++){
        cout << "???" << endl;
    }

    Graph input_graph = Graph(n,m);

    for(int i = 0; i < m; i++){
        cin >> u >> v >> w;
        input_graph.addEdge(u, v, w);
    }

    // Saving the queries
    cin >> l;

    for(int i = 0; i < l; i++){
        cin >> u >> v;
        queries.push_back({u,v});
    }

    cout << "nice" << endl;

    return {input_graph, queries};
}

void get_output(Graph& g, vector<pair<int,int>>& queries){
    for(pair<int,int> query : queries){
        cout << g.itineraries_v1(query.first, query.second);
    }
}

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

    input_graph.makeMST();

    for(pair<int,int> query : queries){
        cout << input_graph.itineraries_v1(query.first, query.second) << endl;
    }

    // cout << "nice" << endl;


    //get_input();

    //input_queries = get_input().second;
    
    // for(pair<int,int> query : input_queries){
    //    cout << query.first << " " << query.second << endl;
    // }
    //get_output(input_graph, input_queries);
    






    // get_output_files();

    

    /*
    Graph g1 = Graph(4,2);
    g1.addEdge(1,2,3);
    g1.addEdge(2,4,5);
    */
   
    // Quickly Testing Union Find
    // UnionFind testUnionFind(10);

    // testUnionFind.print();

    // cout << "Finding parent:" << endl;
    // cout << testUnionFind.findParent(2) << endl;

    // testUnionFind.unionVertices(2,3);
    // testUnionFind.unionVertices(1,2);
    // testUnionFind.unionVertices(3,4);
    // testUnionFind.unionVertices(1,5);
    // testUnionFind.unionVertices(8,3);

    // testUnionFind.print();

    // Quickly testing Graph class
    // int n, m;
    // cin >> n >> m;

    // vector<pair<int,int>> queries;

    // Graph g1 = Graph(n,m);

    // for(int i=0; i < m; i++){
    //     int v1, v2, w;
    //     cin >> v1 >> v2 >> w;
    //     g1.addEdge(v1,v2,w);

    // }

    // g1.print();


    // // cout << g1.itineraries_v1(1,4) << endl;
    // // cout << g1.itineraries_v1(2,4) << endl;
    // // cout << g1.itineraries_v1(1,3) << endl;


    


    // // testing MST
    // g1.makeMST();
    // g1.printMST();

    // g1.get_depth_map();
    // g1.get_ancestors();
    // g1.print_ancestors();


    // cout << "Testing the itineraries: " << endl;
    // bool test;
    // test = g1.itineraries_v1(3,2) == g1.itineraries_v2(3,2);
    // cout << test << endl;

    // test = g1.itineraries_v1(1,3) == g1.itineraries_v2(1,3);
    // cout << test << endl;

    // test = g1.itineraries_v1(2,4) == g1.itineraries_v2(2,4);
    // cout << test << endl;
    
    // //g1.get_depth_map();
    // //g1.print_levels();


    // cout << "Testing the itineraries 3: " << endl;

    // return 0;
}
