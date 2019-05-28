#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>

#include "node.h"
#include "edge.h"

using namespace std;

template <typename N, typename E>
class Graph {
  public:
    typedef Graph <N, E> self;
    typedef Node <N> node;
    typedef Edge <N, E> edge;

    Graph (bool is_directed): is_directed(is_directed) {
      cout << "El grafo se creo" << endl;
    }

    ~Graph () {
      // TO DO
      cout << "Eliminar lo que se tenga que eliminar" << endl;
    }

    // Elvis
    bool addNode (N tag, double x, double y) {
      // ADD NODE
      // RETURNS FALSE IF IT WAS ALREADY IN THE GRAPH
      return true;
    }

    // Elvis
    bool deleteNode (N tag) {
      // DELETE NODE
      // RETURNS FALSE IF THE VERTEX WAS NOT IN THE GRAPH
      return true;
    }

    // Daniel
    bool addEdge (N from, N to, E weight) {
      // ADD EDGE
      // If is_directed == false -> addEdge(to, from, weight)
      // RETURNS FALSE IF THE VERTEX ALREADY EXISTS
      return true;
    }

    // Daniel
    bool deleteEdge (N from, N to) {
      // Tener cuidado con actualizar las dependencias
      // Retornar false si el edge no existia
      return true;
    }

    // Elvis
    node* findNode (N tag) {
      // Retorna un puntero de la ubicacion del vertice `node`
      // retorna NULL si no se encuentra
      node* ret = nullptr;
      return ret;
    }

    // Daniel
    edge* findEdge (N from, N to) {
      // Similar a findVertex
      node* ret = nullptr;
      return ret;
    }

    // Julio
    double getDensity () {
      // TO DO
      double density = 0.0;
      return density;
    }

    // Julio
    bool isSource (N tag) {
      if (!findNode(tag)) throw "The node does not belong to the graph";
      // retorna si `tag` es un nodo fuente
      return true;
    }

    // Julio
    bool isSink (N tag) {
      if (!findNode(tag)) throw "The node does not belong to the graph";
      // retorna si `tag` es un nodo hundido
      return true;
    }

    // Elvis
    int getDegree (N tag) {
      if (!findNode(tag)) throw "The node does not belong to the graph";
      // TO DO
      return 0;  
    }

    // Daniel
    self Prim () {
      if (is_directed) throw "The graph must be undirected";
      self mst(is_directed);
      return move(mst);
    }

    // Elvis
    self Kruskal () {
      if (is_directed) throw "The graph must be undirected";
      self mst(is_directed);
      return move(mst);
    }

    // Julio
    // Retorno un vector de pares {etiqueta de un nodo, level de ese nodo}
    vector <pair <N, int>> BFS (N source) {
      if (!findNode(source)) throw "The node does not belong to the graph";
      vector <pair <N, int>> ret;
      return ret;
    }

    // Julio
    // Retorno un vector de pares {etiqueta de un nodo, {tiempo de entrada, tiempo de salida}}
    vector <pair <N, pair <int, int>>> dfs (N source) {
      if (!findNode(source)) throw "The node does not belong to the graph";
      vector <pair <N,pair <int, int>>> ret;
      return ret;
    }

    
    // Retorna si el grafo es conexo
    bool isConex () {
      return true;
    }

    // Leonidas
    bool isBipartite () {
      const bool BLACK = false;
      const bool WHITE = true;
      map <N, bool> color;
      for (node current: nodeList) {
        N cur_tag = current -> getTag();
        if (color.count(cur_tag) == 0) {
          queue <N> Q;
          Q.push(cur_tag);
          color[cur_tag] = BLACK;
          while (not Q.empty()) {
            N u = Q.front();
            Q.pop();
            for (N v: adjList[u]) {
              if (color.count(v) == 0) {
                color[v] = (color[u] == BLACK) ? WHITE : BLACK;
              } else if (color[u] == color[v]) return false;
            }
          }
        }
      }
      return true;
    }

    // Leonidas
    bool isStronglyConnected () {
      // TO DO
      return true;
    }

  private:

    const double denseParameter = 0.5;
    set <node> nodeList;
    set <edge> edgeList;
    map <N, set <N>> adjList;
    bool is_directed;
};

#endif
