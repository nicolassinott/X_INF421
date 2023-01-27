#include <iostream>
#include <cmath>
#include "Graph.h"

using namespace std;

int main(){
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
    int n, m;
    cin >> n >> m;

    Graph g1 = Graph(n,m);

    for(int i=0; i < m; i++){
        int v1, v2, w;
        cin >> v1 >> v2 >> w;
        g1.addEdge(v1,v2,w);

    }

    g1.print();


    // cout << g1.itineraries_v1(1,4) << endl;
    // cout << g1.itineraries_v1(2,4) << endl;
    // cout << g1.itineraries_v1(1,3) << endl;


    


    // testing MST
    g1.makeMST();
    g1.printMST();

    g1.get_depth_map();
    g1.get_ancestors();
    g1.print_ancestors();


    cout << "Testing the itineraries: " << endl;
    bool test;
    test = g1.itineraries_v1(3,2) == g1.itineraries_v2(3,2);
    cout << test << endl;

    test = g1.itineraries_v1(1,3) == g1.itineraries_v2(1,3);
    cout << test << endl;

    test = g1.itineraries_v1(2,4) == g1.itineraries_v2(2,4);
    cout << test << endl;
    
    //g1.get_depth_map();
    //g1.print_levels();

    return 0;
}
