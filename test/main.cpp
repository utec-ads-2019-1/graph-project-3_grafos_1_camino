//#include <graphL/graphlut.h>
#include <iostream>

#include "graph.h"

using namespace std;

int main (int argc, char *argv[]) {
  try {
    Graph <char, int>* graph = new Graph <char, int> (false);
    graph -> addNode('a', 0.0, 0.0);
    graph -> addNode('b', 1.1, 1.1);
    graph -> addNode('c', 1.1, 1.1);
    graph -> addNode('d', 1.1, 1.1);
    graph -> addNode('e', 1.1, 1.1);
    //graph -> addEdge('a', 'b', 4);
   //graph -> deleteEdge('a', 'b');
    if (graph -> findNode('h')) cout << "a esta en el grafo" << endl;
    //graph -> Prim();
    //delete graph;
  } catch (const char* msg) {
    cerr << msg << endl;
  }
  return EXIT_SUCCESS;
}
