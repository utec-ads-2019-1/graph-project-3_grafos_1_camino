#include <iostream>

#include "../Graph/graph.h"

using namespace std;

Graph <char, float>* graph;

void testAddNode () {
  if (!graph -> addNode('a', 0.0, 0.0)) cerr << "Error inserting node 'a'" << endl;
  if (!graph -> addNode('b', 1.0, 0.0)) cerr << "Error inserting node 'a'" << endl;
  if (!graph -> addNode('c', 0.0, 1.0)) cerr << "Error inserting node 'a'" << endl;
}

void testFindNode() {
  if (!graph -> findNode('a')) cerr << "Error in findNode 'a'" << endl;
  if (!graph -> findNode('b')) cerr << "Error in findNode 'a'" << endl;
  if (!graph -> findNode('c')) cerr << "Error in findNode 'a'" << endl;
}

void testAddEdge () {
  if (!graph -> addEdge('a', 'b', 10.0)) cerr << "Error inserting edge (a, b, 10)" << endl;
  if (!graph -> addEdge('a', 'c', 11.0)) cerr << "Error inserting edge (a, b, 10)" << endl;
  if (!graph -> addEdge('c', 'b', 12.0)) cerr << "Error inserting edge (a, b, 10)" << endl;
}

void testFindEdge () {
  if (!graph -> findEdge('a', 'b')) cerr << "Error finding edge (a, b, 10)" << endl;
  if (!graph -> findEdge('a', 'c')) cerr << "Error finding edge (a, b, 10)" << endl;
  if (!graph -> findEdge('c', 'b')) cerr << "Error finding edge (a, b, 10)" << endl;
}

void testProperties () {
  if (graph -> isSink('a')) cerr << "isSink is not working for 'a'" << endl;
  if (graph -> isSink('b')) cerr << "isSink is not working for 'b'" << endl;
  if (graph -> isSink('c')) cerr << "isSink is not working for 'c'" << endl;
  if (graph -> isSource('a')) cerr << "isSource is not working for 'a'" << endl;
  if (graph -> isSource('b')) cerr << "isSource is not working for 'b'" << endl;
  if (graph -> isSource('c')) cerr << "isSource is not working for 'c'" << endl;
  // graph -> ImprimirGrafo();
  // Error construyendo adList_Trans
}

void testPrim () {
  for (char ch: {'a', 'b', 'c'}) {
    Graph <char, float> mst = graph -> Prim(ch);
    if (!mst.findNode('a')) cerr << "Prim is not working" << endl;
    if (!mst.findNode('b')) cerr << "Prim is not working" << endl;
    if (!mst.findNode('c')) cerr << "Prim is not working" << endl;
  }
}

void testKruskal () {
  Graph <char, float> mst = graph -> Kruskal();
  if (!mst.findNode('a')) cerr << "Prim is not working" << endl;
  if (!mst.findNode('b')) cerr << "Prim is not working" << endl;
  if (!mst.findNode('c')) cerr << "Prim is not working" << endl;

}

void testBFS () {
  map <char, int> levels = graph -> BFS('a');
  if (levels['a'] != 0) cerr << "BFS is not working for 'a'" << endl;
  if (levels['b'] != 1) cerr << "BFS is not working for 'b'" << endl;
  if (levels['c'] != 1) cerr << "BFS is not working for 'c'" << endl;
}

void testDFS () {
  map <char, pair <int, int>> times = graph -> DFS('a');
  if (times['a'].first != 0) cerr << "DFS is not working for 'a'" << endl;
  if (times['a'].second != 5) cerr << "DFS is not working for 'a'" << endl;
  if (times['b'].first != 1) cerr << "DFS is not working for 'b'" << endl;
  if (times['b'].second != 4) cerr << "DFS is not working for 'b'" << endl;
  if (times['c'].first != 2) cerr << "DFS is not working for 'c'" << endl;
  if (times['c'].second != 3) cerr << "DFS is not working for 'c'" << endl;
}

void testConex () {
  if (!graph -> isConex()) cerr << "isConex is not working" << endl;
}

void testBipartite () {
  if (graph -> getBipartiteAndColors().first) cerr << "IsBipartite is now working" << endl;
}

void testSCC () {
  pair <int, map <char, int>> ret = graph -> getStronglyConnectedComponents ();
  if (ret.first != 1) cerr << "SCC is not working" << endl;
  map <char, int> components = ret.second;
  if (components['a'] != components['b']) cerr << "SCC is not working" << endl;
  if (components['a'] != components['c']) cerr << "SCC is not working" << endl;
  if (components['b'] != components['c']) cerr << "SCC is not working" << endl;
}

void testDeleteNodeAndEdge () {
  // TO DO
}

int main (int argc, char *argv[]) {
  try {
    graph = new Graph <char, float> (false);
    testAddNode();
    testFindNode();
    testAddEdge();
    testFindEdge();
    testProperties();
    // testPrim(); Not working
    // testKruskal(); Not implemented
    testDFS();
    testBFS();
    testConex();
    testBipartite();
    testSCC();
    testDeleteNodeAndEdge();
    delete graph;
  } catch (const char* msg) {
    cerr << msg << endl;
  }
  return EXIT_SUCCESS;
}
