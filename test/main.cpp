//#include <graphL/graphlut.h>
#include <iostream>

#include "graph.h"

using namespace std;

int main (int argc, char *argv[]) {
  try {
    Graph <char, int>* graph = new Graph <char, int> (false);
    if (graph -> addNode('a', 0.0, 0.0)) cout<< "se creo el nodo a"<<endl;
    if (graph -> addNode('b', 1.1, 1.1)) cout<< "se creo el nodo b"<<endl;
    if (graph -> addNode('c', 1.1, 1.1)) cout<< "se creo el nodo c"<<endl;
    if (graph -> addNode('d', 1.1, 1.1)) cout<< "se creo el nodo d"<<endl;
    if (graph -> addNode('e', 1.1, 1.1)) cout<< "se creo el nodo e"<<endl;
    if (graph -> deleteNode('b')) cout<< "se elimino el nodo b"<<endl;
    //graph -> addEdge('a', 'b', 4);
   //graph -> deleteEdge('a', 'b');
    if (graph -> findNode('a')) cout << "a esta en el grafo" << endl;
    //graph -> Prim();
    //delete graph;
  } catch (const char* msg) {
    cerr << msg << endl;
  }
  return EXIT_SUCCESS;
}
