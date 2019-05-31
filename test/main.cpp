//#include <graphL/graphlut.h>
#include <iostream>

#include "graph.h"

using namespace std;

int main (int argc, char *argv[]) {
  try {
    Graph <char, int>* graph = new Graph <char, int> (false);
    if (!graph -> addNode('a', 0.0, 0.0)) cerr << "Error inserting node 'a'" << endl;
    if (!graph -> addNode('b', 1.1, 1.1)) cerr << "Error inserting node 'a'" << endl;
    if (!graph -> addNode('c', 1.1, 1.1)) cerr << "Error inserting node 'a'" << endl;
    if (!graph -> addNode('d', 1.1, 1.1)) cerr << "Error inserting node 'a'" << endl;
    if (!graph -> addNode('e', 1.1, 1.1)) cerr << "Error inserting node 'a'" << endl;
    if (!graph -> addNode('f', 1.1, 1.1)) cerr << "Error inserting node 'a'" << endl;
    if (!graph -> addNode('g', 1.1, 1.1)) cerr << "Error inserting node 'a'" << endl;

    //if (!graph -> addEdge('a', 'b', 4)) cerr << "Error inserting edge 'a' -> 'b'" << endl;
    //if (!graph -> addEdge('f', 'a', 4)) cerr << "Error inserting edge 'f' -> 'a'" << endl;

    graph -> addEdge('a', 'b', 2);
    graph -> addEdge('b', 'c', 1);
    graph -> addEdge('b', 'd', 3);
    graph -> addEdge('b', 'e', 7);
    graph -> addEdge('d', 'e', 5);
    graph -> addEdge('e', 'f', 8);
    graph -> addEdge('f', 'g', 1);

    cout << graph->getOutDegree('a')<<endl;
    cout << graph->getInDegree('a')<<endl;
    cout << graph->getInDegree('b')<<endl;
    cout << graph->getInDegree('f')<<endl;
    graph -> ImprimirGrafo();
    //graph -> deleteEdge ('a','b');
    //u7hhhhhhhhhhhhhhhhhhhhhhhhh77hh77hgraph -> deleteEdge ('c','b');
    graph -> ImprimirGrafo();
    //graph -> ImprimirGrafo();
    //graph -> ImprimirGrafo();
    //graph -> deleteEdge('a', 'b');
    if (graph -> findNode('a')) cout << "a esta en el graphrafo" << endl;
    if (graph -> findNode('f')) cout << "b esta en el graphrafo" << endl;
    if (graph -> findEdge('a','b')) cout << "a b esta en el graphrafo" << endl;
    //if (graph -> findEdge('a','c')) cout << "ab esta en el graphrafo" << endl;
    Graph <char, int> graph2 = graph -> Kruskal();
    //graph2.ImprimirGrafo();
    delete graph;
  } catch (const char* msg) {
    cerr << msg << endl;
  }
  return EXIT_SUCCESS;
}
