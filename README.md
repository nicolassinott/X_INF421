# 🌳 Most Pleasant Itineraries

This repository contains the implementation of the "Most Pleasant Itineraries" project from the Conception of Algorithms course INF421 of École Polytechnique.

Given a multigraph, it computes its minimal spanning tree (MST) and uses it to compute the path of lowest noise between vertices. The noise of path being defined as the edge with highest noise.

There are three different versions of the algorithm: 

- itineraries_v1: computes the MST and answers queries naively by a depth-first traversal search. Complexity of MST is $O(\text{n log(n)})$ and search $O(\text{n})$.
- itineraries_v2: computes the MST, stores the power of two ancestors of each vertex in a tree starting from the vertex 1, computes each query by searching for the lowest common ancestor of both vertices. Complexity of MST is $O(\text{n log(n)})$ and search $O(\text{log(n)})$.
- itineraries_v3: slighly modification on the Tarjan's lowest common ancestors algorithm to reduce the complexity even further. Complexity of MST is $O(\text{n log(n)})$, preprocessing $O(\text{n})$, then each query is constant in average. 

The project's guidelines can also be found in this repository. More information can be found in the report.

## 🚀 Running and Compiling

To run the input files (stored in the `input` folder): 
```bash
bash ./run.sh
```

To change the version of the algorithm you must change it in the `main.cpp` and `run.sh`.

## 💻 Results

You can find the results of the queries by checking the outputs folder and the time of execution in the time folder.
