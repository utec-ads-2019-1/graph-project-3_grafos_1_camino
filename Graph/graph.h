#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <typeinfo>
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
      cout << "Elim=inar lo que se tenga que eliminar" << endl;
    }

    // Elvis
    bool addNode (N tag, double x, double y) {
      if (findNode(tag)) return false;
      for (auto it = nodeList.begin(); it != nodeList.end(); it++ ){
        if (it -> getX() == x && it -> getY() == y) return false;
      }
      node newNode = node(tag,x,y);
      set <N> AdjNodes;
      adjList.insert({newNode.getTag(), AdjNodes});
      adjList_Trans.insert({newNode.getTag(), AdjNodes});
      nodeList.insert(newNode);
      return true;  
    }

    // Elvis
    bool deleteNode (N tag) {
      if (!findNode(tag)) return false;
      auto node = adjList.find(tag);
      auto it = adjList.find(tag);
      for (auto i : node -> second){
        it = adjList.find(i);
        it->second.erase(tag);
      }
      adjList.erase(tag);
      for (auto i = nodeList.begin(); i != nodeList.end(); i++){
        if (i -> getTag() == tag) nodeList.erase(i);
      }
      if (!is_directed)  return true;
      node = adjList_Trans.find(tag);
      for (auto i : node -> second){
        it = adjList.find(i);
        it->second.erase(tag); 
      }
      adjList_Trans.erase(tag);
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
      auto it_set = adjList.find(tag);
        if ( it_set != adjList.end()){
          for ( auto it_set : nodeList){
            if (it_set.getTag() == tag){
                node* ret = &it_set;
                return ret;
            }
          }
        }
      return nullptr;  
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

    //Elvis
    int getDegree (N tag) { 

      return getOutDegree(tag); 
    }
    
    //Elvis
    int getOutDegree (N tag){
      if (!findNode(tag)) throw "The node doesn't belong to the graph";
      auto node = adjList.find(tag);
      int outDegree = node -> second.size();
      return outDegree; 
    }   

    int getInDegree(N tag){  
      if (!findNode(tag)) throw "The node doesn't belong to the graph";
      auto node = adjList_Trans.find(tag);
      int inDegree = node -> second.size();
      return inDegree; 
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
      set <N> nodes;
      auto itSet = edgeList.begin();
      int count = nodeList.size();
      pair <N, N> pairNodes;
      while (count > 0){
        pairNodes = itSet->getNodes();
        int flag0 = 0, flag1 = 0;
        if (nodes.find(pairNodes.first) != nodes.end()) flag0++;
        if (nodes.find(pairNodes.second) != nodes.end()) flag1++;
        if ((flag0 + flag1) > 1){
          itSet++;
          continue;
        }
        if(flag0){
          nodes.insert(pairNodes.first);
          mst.addNode(pairNodes.first);
          count--;
        }
        if(flag1){
          nodes.insert(pairNodes.second);
          mst.addNode(pairNodes.second);
          count--;
        }
        mst.addEdge(pairNodes.first, pairNodes.second, itSet->getWeight());
        itSet++;
      }  
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
    set <node> nodeList;
    set <edge> edgeList;
    map <N, set <N>> adjList;
    map <N, set <N>> adjList_Trans;
    bool is_directed = false;
};

#endif
