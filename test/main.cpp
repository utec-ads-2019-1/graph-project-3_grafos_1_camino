#include <iostream>

#include "../Graph/graph.h"

using namespace std;

Graph <char, float>* graph;

void testAddNode () {
  if (!graph -> addNode('a', 0.0, 0.0)) cerr << "Error inserting node 'a'" << endl;
  if (!graph -> addNode('b', 1.0, 0.0)) cerr << "Error inserting node 'a'" << endl;
  if (!graph -> addNode('c', 0.0, 1.0)) cerr << "Error inserting node 'a'" << endl;
  if (!graph -> addNode('d', 2.0, 0.0)) cerr << "Error inserting node 'a'" << endl;
  if (!graph -> addNode('e', 0.0, 2.0)) cerr << "Error inserting node 'a'" << endl;
  if (!graph -> addNode('f', 3.0, 1.0)) cerr << "Error inserting node 'a'" << endl;
  if (!graph -> addNode('g', 0.0, 3.0)) cerr << "Error inserting node 'a'" << endl;
  if (!graph -> addNode('h', 0.0, 9.0)) cerr << "Error inserting node 'a'" << endl;  
  
}

void testFindNode() {
  if (!graph -> findNode('a')) cerr << "Error in findNode 'a'" << endl;
  if (!graph -> findNode('b')) cerr << "Error in findNode 'a'" << endl;
  if (!graph -> findNode('c')) cerr << "Error in findNode 'a'" << endl;
}

void testAddEdge () {
  if (!graph -> addEdge('a', 'b', 2.0)) cerr << "Error inserting edge (a, b, 2)" << endl;
  if (!graph -> addEdge('b', 'c', 1.0)) cerr << "Error inserting edge (b, c, 1)" << endl;
  if (!graph -> addEdge('b', 'd', 3.0)) cerr << "Error inserting edge (b, d, 3)" << endl;
  if (!graph -> addEdge('b', 'e', 7.0)) cerr << "Error inserting edge (b, e, 7)" << endl;
  if (!graph -> addEdge('d', 'e', 5.0)) cerr << "Error inserting edge (d, e, 5)" << endl;
  if (!graph -> addEdge('e', 'f', 8.0)) cerr << "Error inserting edge (e, f, 8)" << endl;
  if (!graph -> addEdge('f', 'g', 1.0)) cerr << "Error inserting edge (f, g, 1)" << endl;
}

void testFindEdge () {
  if (!graph -> findEdge('a', 'b')) cerr << "Error finding edge (a, b, 10)" << endl;
  if (!graph -> findEdge('b', 'd')) cerr << "Error finding edge (a, b, 10)" << endl;
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
  /*  if (!mst.findNode('d')) cerr << "Prim is not working" << endl;
    if (!mst.findNode('e')) cerr << "Prim is not working" << endl;
    if (!mst.findNode('f')) cerr << "Prim is not working" << endl;
    if (!mst.findNode('g')) cerr << "Prim is not working" << endl;
    if (!mst.findNode('h')) cerr << "Prim is not working" << endl;*/
  }
}

void testKruskal () {
  Graph <char, float> mst = graph -> Kruskal();
  set <Node <char>> nodes = mst.getNodeList();
  if (!mst.findNode('a')) cerr << "Kruskal is not working 'a'" << endl;
  if (!mst.findNode('b')) cerr << "Kruskal is not working 'b'" << endl;
  if (!mst.findNode('c')) cerr << "Kruskal is not working 'c'" << endl;
  if (!mst.findNode('d')) cerr << "Kruskal is not working 'd'" << endl;
  if (!mst.findNode('e')) cerr << "Kruskal is not working 'e'" << endl;
  if (!mst.findNode('f')) cerr << "Kruskal is not working 'f'" << endl;
  if (!mst.findNode('g')) cerr << "Kruskal is not working 'g'" << endl;
  if (!mst.findNode('h')) cerr << "Kruskal is not working 'h'" << endl;
}

void testBFS () {
  map <char, int> levels = graph -> BFS('a');
  if (levels['a'] != 0) cerr << "BFS is not working for 'a'" << endl;
  if (levels['b'] != 1) cerr << "BFS is not working for 'b'" << endl;
  if (levels['c'] != 2) cerr << "BFS is not working for 'c'" << endl;
  if (levels['d'] != 2) cerr << "BFS is not working for 'd'" << endl;
  if (levels['e'] != 2) cerr << "BFS is not working for 'e'" << endl;
  if (levels['f'] != 3) cerr << "BFS is not working for 'f'" << endl;
  if (levels['g'] != 4) cerr << "BFS is not working for 'g'" << endl;
}

void testDFS () {
  map <char, pair <int, int>> times = graph -> DFS('a');
  if (times['a'].first != 0) cerr << "DFS is not working for 'a'" << endl;
  if (times['a'].second != 13) cerr << "DFS is not working for 'a'" << endl;
  if (times['b'].first != 1) cerr << "DFS is not working for 'b'" << endl;
  if (times['b'].second != 12) cerr << "DFS is not working for 'b'" << endl;
  if (times['c'].first != 2) cerr << "DFS is not working for 'c'" << endl;
  if (times['c'].second != 3) cerr << "DFS is not working for 'c'" << endl;
  if (times['d'].first != 4) cerr << "DFS is not working for 'd'" << endl;
  if (times['d'].second != 11) cerr << "DFS is not working for 'd'" << endl;
  if (times['e'].first != 5) cerr << "DFS is not working for 'e'" << endl;
  if (times['e'].second != 10) cerr << "DFS is not working for 'e'" << endl;
  if (times['f'].first != 6) cerr << "DFS is not working for 'f'" << endl;
  if (times['f'].second != 9) cerr << "DFS is not working for 'f'" << endl;
  if (times['g'].first != 7) cerr << "DFS is not working for 'g'" << endl;
  if (times['g'].second != 8) cerr << "DFS is not working for 'g'" << endl;
}

void testConex () {
  if (graph -> isConex()) cerr << "isConex is not working" << endl;
}

void testBipartite () {
  if (graph -> getBipartiteAndColors().first) cerr << "IsBipartite is now working" << endl;
}

void testSCC () {
  pair <int, map <char, int>> ret = graph -> getStronglyConnectedComponents ();
  if (ret.first != 2) cerr << "SCC is not giving the correct number of SCC" << endl;
  map <char, int> components = ret.second;
  if (components['a'] != 2) cerr << "SCC is not working" << endl;
  if (components['b'] != 2) cerr << "SCC is not working" << endl;
  if (components['c'] != 2) cerr << "SCC is not working" << endl;
  if (components['d'] != 2) cerr << "SCC is not working" << endl;
  if (components['e'] != 2) cerr << "SCC is not working" << endl;
  if (components['f'] != 2) cerr << "SCC is not working" << endl;
  if (components['g'] != 2) cerr << "SCC is not working" << endl;
  if (components['h'] != 1) cerr << "SCC is not working" << endl;
}

void testDeleteNodeAndEdge () {
  graph -> deleteNode('a');
}

int main (int argc, char *argv[]) {
  try {
    graph = new Graph <char, float> (false);
    graph -> addNode('a', 0.0, 0.0);
    graph -> addNode('b', 0.0, 1.0);
    graph -> addNode('c', 0.0, 2.0);
    graph -> addNode('d', 1.0, 0.0);
    graph -> addNode('e', 1.0, 1.0);
    graph -> addNode('f', 1.0, 2.0);
    graph -> addNode('g', 2.0, 0.0);
    graph -> addNode('h', 2.0, 1.0);
    graph -> addNode('i', 2.0, 2.0);

    graph -> addEdge('a', 'b', 1.0);
    graph -> addEdge('b', 'c', 1.0);
    graph -> addEdge('b', 'e', 1.0);
    graph -> addEdge('h', 'e', 1.0);
    graph -> addEdge('d', 'e', 1.0);
    graph -> addEdge('e', 'f', 1.0);
    graph -> addEdge('g', 'h', 1.0);
    graph -> addEdge('h', 'i', 1.0);
    graph -> addEdge('a', 'd', 1.0);
    graph -> addEdge('d', 'g', 1.0);
    graph -> addEdge('c', 'f', 1.0);
    graph -> addEdge('i', 'f', 1.0);


    graph->A_asterisk('a','i').ImprimirGrafo();

    delete graph;
  } catch (const char* msg) {
    cerr << msg << endl;
  }
  return EXIT_SUCCESS;
}
