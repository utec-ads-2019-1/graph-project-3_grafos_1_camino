#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <map>

#include "node.h"
#include "edge.h"

#include <iostream>

using namespace std;

template <typename N, typename E>
class Graph {
  public:
    typedef Graph <N, E> self;
    typedef Node <N> node;
    typedef Edge <N, E> edge;
    typedef vector <node*> NodeSeq;
    typedef vector <edge*> EdgeSeq;
    typedef typename NodeSeq::iterator NodeIte;
    typedef typename EdgeSeq::iterator EdgeIte;

    Graph (bool is_directed): is_directed(is_directed) {
      cout << "El grafo se creo" << endl;
    } 
    ~Graph () {
      // TO DO
    }

    // Elvis
    bool addNode (N tag, double x, double y) {
      // ADD NODE
      // RETURNS FALSE IF IT WAS ALREADY IN THE GRAPH
    }

    // Elvis
    bool deleteNode (N tag) {
      // DELETE NODE
      // RETURNS FALSE IF THE VERTEX WAS NOT IN THE GRAPH
    }

    // Daniel
    bool addEdge (N from, N to, E weight) {
      // ADD EDGE
      // If is_directed == false -> addEdge(to, from, weight)
      // RETURNS FALSE IF THE VERTEX ALREADY EXISTS
    }

    // Daniel
    bool deleteEdge (N from, N to) {
      // Tener cuiado con actualizar las dependencias
    }

    // Elvis
    node* findNode (N tag) {
      // Retorna un puntero de la ubicacion del vertice `node`
      // retorna end(NodeSeq) si no se encuentra
    }

    // Daniel
    edge* findEdge (N from, N to) {
      // Similar a findVertex
    }

    // Julio
    double getDensity () {
      // TO DO
    }

    // Julio
    bool esFuente (N tag) {
      // retorna si `tag` es un nodo fuente
    }

    // Julio
    bool esHundido (N tag) {
      // retorna si `tag` es un nodo hundido
    }

    // Elvis
    int getDegree (N tag) {
      // TO DO      
    }

    // Daniel
    self Prim () {}

    // Elvis
    self Kruskal () {}

    // Julio
    // Retorno un vector de pares {etiqueta de un nodo, level de ese nodo}
    vector <pair <N, int>> BFS (N source) {}

    // Julio
    // Retorno un vector de pares {etiqueta de un nodo, {tiempo de entrada, tiempo de salida}}
    vector <pair <N, pair <int, int>>> dfs (N source) {
    }

    
    // Retorna si el grafo es conexo
    bool isConex () {
    
    }

    // Leonidas
    bool isBipartite () {}

    // Leonidas
    bool isStronglyConnected () {
      // TO DO
    }

  private:

    const double denseParameter = 0.5;

    NodeSeq nodes;
    EdgeSeq edgeList;
    map <node, NodeSeq> adjList;
    NodeIte ni;
    EdgeIte ei;
    bool is_directed;
};

#endif
