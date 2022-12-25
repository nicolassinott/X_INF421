#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

class Graph{
    public:
        int n;
        int m;
        map<int, map<int,int>> edges;
        map<int, map<int,int>> mst;

        Graph(int n, int m){
            for(int i = 1; i <= n; i++){
                edges[i] = {};
            }
        }

        void addEdge(int v1, int v2, int w){
            edges[v1].insert({v2,w});
            edges[v2].insert({v1,w});
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

        void makeMST(){ // make mst

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

            cout << "Checking if the vector is sorted" << endl;
            for(vector<int> v : priorityQueue){
                cout << v[0] << ' ' << v[1] << ' ' << v[2] << endl;
            }

            return;
        }

        int itineraries_v1(int u, int v){ // assuming mst

            // verifica se MST ja existe, senao makeMST();

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

                for (auto const& [neighbor, weight] : edges[curr]){
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
                maxWeight = max(maxWeight, edges[currNode][next]); //
                currNode = next;
            }

            return maxWeight;
        }

};
