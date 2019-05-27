#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <set>
#include <map>

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

      if(!findNode(tag)) throw "The node was already in the graph";
      else{
        newNode= new Node(tag,x,y);
        adjList.insert(newNode,AdjNodes <Node>);
        adjList_Trans.insert(newNode,AdjNodes <Node>);
        return true;
      }  
    }

    // Elvis
    bool deleteNode (N tag) {
      if(!findNode(tag)) throw "The node doesn't belong to the graph";
      if(!is_directed){
        auto it_map=adjList.
        for(auto = )
      }
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
      auto it_map=adjList.find(tag);
      if (it_map == adjList.end()) return nullptr;
      else  return &(it->first);
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
      if (!findNode(tag)) throw "The node doesn't belong to the graph"; 
      if (!is_directed) {
        auto node = adjList.find(tag);
        int degree = node->second.size();
        return degree;
      } else{
        auto node = adjList.find(tag);
        int outDegree = node->second.size();
        node = adjList_Trans.find(tag);
        int inDegree = node->second.size(); 
        }  
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
    bool isBipartite () {}

    // Leonidas
    bool isStronglyConnected () {
      // TO DO
    }

  private:

    const double denseParameter = 0.5;
    set <edge> edgeList;
    map <node, set <Node>> adjList;
    map <node, set <Node>> adjList_Trans;
    bool is_directed;
};

#endif
