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

    int n, m;
    cin >> n >> m;

    Graph g1 = Graph(n,m);

    for(int i=0; i < m; i++){
        int v1, v2, w;
        cin >> v1 >> v2 >> w;
        g1.addEdge(v1,v2,w);

    }

    g1.print();

    //g1.itineraries_v1(1,4);

    cout << g1.itineraries_v1(1,4) << endl;
    cout << g1.itineraries_v1(2,4) << endl;
    cout << g1.itineraries_v1(1,3) << endl;

    return 0;
}
