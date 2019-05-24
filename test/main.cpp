//#include <graphL/graphlut.h>
#include <iostream>

#include "graph.h"

using namespace std;

int main (int argc, char *argv[]) {
  try {
    Graph <char, int>* graph = new Graph <char, int> (false);
    graph -> addNode('a', 0.0, 0.0);
    graph -> addNode('b', 1.1, 1.1);
    graph -> addEdge('a', 'b', 4);
    graph -> deleteEdge('a', 'b');
    if (graph -> findNode('a')) cout << "a esta en el graphrafo" << endl;
    graph -> Prim();
    delete graph;
  } catch (const char* msg) {
    cerr << msg << endl;
  }
  return EXIT_SUCCESS;
}
