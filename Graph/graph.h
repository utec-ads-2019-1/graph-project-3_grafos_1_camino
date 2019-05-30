#ifndef GRAPH_H
#define GRAPH_H

#include <functional>
#include <iostream>
#include <typeinfo>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <typeinfo>
#include "node.h"
#include "edge.h"

using namespace std;

template <typename N, typename E>
class Graph {
public:
    typedef Graph <N, E> self;
    typedef Node <N> node;
    typedef Edge <N, E> edge;

    Graph (bool is_directed): is_directed(is_directed) {}

    ~Graph () {
      nodeList.clear();
      edgeList.clear();
      adjList.clear();
      adjList_Trans.clear();
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
      auto itMap = adjList.find(tag);
      for (auto itSet : node -> second){
        itMap = adjList.find(itSet);
        itMap->second.erase(tag);
      }
      adjList.erase(tag);
      for (auto i = nodeList.begin(); i != nodeList.end(); i++){
        if (i -> getTag() == tag) nodeList.erase(tag);
      }
      node = adjList_Trans.find(tag);
      for (auto i : node -> second){
        itMap = adjList.find(i);
        itMap->second.erase(tag); 
      }
      adjList_Trans.erase(tag);
      return true;
    }

    // Daniel
    bool addEdge (N from, N to, E weight) {
      if(findEdge(from,to))
        return false;
      if(from == to)
        return false;
      edge newEdge1 =  edge(from,to,weight);
      edgeList.insert(newEdge1);
      adjList[from].insert(to);
      adjList_Trans[to].insert(from);
      if(!is_directed){
        edge newEdge2 =  edge(to,from,weight);
        edgeList.insert(newEdge2);
        adjList[to].insert(from);
        adjList_Trans[from].insert(to);
      }
      return true;
    }

    // Daniel
    bool deleteEdge (N from, N to) {
            if(!findEdge(from,to))
            return false;
      if(is_directed) {
          adjList[from].erase(to);
          adjList_Trans[to].erase(from);
          edge* del = findEdge(from,to);
          auto itr = edgeList.find(*del);
          edgeList.erase(itr);
      } else{
          adjList[from].erase(to);
          adjList[to].erase(from);
          adjList_Trans[from].erase(to);
          adjList_Trans[to].erase(from);

          auto itr = edgeList.begin();
          while (itr != edgeList.end()){
              edge ed = *itr;
              if(ed.getNodes().first==from and ed.getNodes().second==to){
                  edgeList.erase(itr);
              }
              if(ed.getNodes().first==to and ed.getNodes().second==from){
                  edgeList.erase(itr);
              }
              itr++;     
          }
      }  
      return true;
   }

    // Elvis
    node* findNode (N tag) {
      for ( auto it_set : nodeList){
        if (it_set.getTag() == tag){
          node* ret = &it_set;
          return ret;
        }
      }
      return nullptr;  
     }  

    // Daniel
    edge* findEdge (N from, N to) {
      for (auto ed : edgeList){
        if(ed.getNodes().first==from and ed.getNodes().second==to){
          edge* ret = &ed;
          return ret;
        }
      }

      return nullptr;
    }

    // Julio
    double getDensity () {
        if (getNumberOfNodes() <= 1) throw "Division by zero";
        double density = 0.0;
        if (is_directed== true){
            density=(getNumberOfEdges()/(getNumberOfNodes()*(getNumberOfNodes()-1)));
        } else{
            density=(2*getNumberOfEdges()/(getNumberOfNodes()*(getNumberOfNodes()-1)));
        }
        return density;
    }

    // Julio
    bool isSource (N tag) {
        if (!findNode(tag)) throw "The node does not belong to the graph";
        // retorna si `tag` es un nodo fuente
        //for (auto i : edgeList){
            //if(i.getNodes().second==tag){
                //return false;
                //}
            //}
        if (this->getInDegree(tag)==0){
            return true;
        }

        return false;

    }

    // Julio
    bool isSink (N tag) {
        if (!findNode(tag)) throw "The node does not belong to the graph";
        // retorna si `tag` es un nodo hundido
        //for (auto i : edgeList){
            //if(i.getNodes().first==tag){
                //return false;
            //}
        //
        if (this->getOutDegree(tag)==0){
            return true;
        }

        return false;
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
    self Prim (N tag) {
      if (is_directed) throw "The graph must be undirected";

      self mst(is_directed);

      node* current = findNode(tag);
      set <N> currentNodes;
      mst.addNode(current->getTag(),current->getX(),current->getY());
      currentNodes.insert(tag);

      int i = 1;
      while (current){
        vector<edge> availableEdges;
        for (auto A : currentNodes){
          for (auto it = adjList.begin();it != adjList.end();it++){
            if(A == it->first){
              for (auto B: it->second){
                auto it2 = currentNodes.find(B);
                if(it2!=currentNodes.end()){
                } else{
                  if(findEdge(A,B)){
                    edge* ed  = findEdge(A,B);
                    edge e = *ed;
                    availableEdges.push_back(e);
                  }
                }
              }
            }

          }
        }
        if(availableEdges.empty()){
          current = nullptr;
        } else{
          edge* e = &availableEdges[0];
          for(auto ed: availableEdges){
            if(e->getWeight()>ed.getWeight())
              e = &ed;
          }
          current = findNode(e->getNodes().second);
          mst.addNode(current->getTag(),current->getX(),current->getY());
          mst.addEdge(e->getNodes().first,e->getNodes().second,e->getWeight());
          currentNodes.insert(current->getTag());
        }
        availableEdges.clear();
        i++;
      }
      return move(mst);
    }
    // Elvis
    self Kruskal () {
      if (is_directed) throw "The graph must be undirected";
      self mst(is_directed);
      set <N> nodes;
      auto itSet = edgeList.begin();
      pair <N, N> pairNodes;
      bool ready = false;
      while (itSet!= edgeList.end() ){
          pairNodes = itSet -> getNodes();
          int flag0 = 0, flag1 = 0;
          if (nodes.find(pairNodes.first) != nodes.end()) flag0++;
          if (nodes.find(pairNodes.second) != nodes.end()) flag1++;
          if ((flag0 + flag1) > 1){
              map <N, int> bfsP =  mst.BFS(pairNodes.first);
              bool is = false;
              for (auto it: bfsP){
                  if (it.first == pairNodes.second){
                      is = true;
                      break;
                  }
              }
              if (!is){
                  mst.addEdge(pairNodes.first, pairNodes.second, itSet -> getWeight());
              }
              itSet++;
              itSet++;
              if (itSet == edgeList.end()) break;
              continue;
          }
          if(flag0 == 0){
              node* node = findNode(pairNodes.first);
              nodes.insert(node -> getTag());
              mst.addNode(node -> getTag(), node -> getX(), node -> getY());
          }
          if (flag1 == 0){
              node* node = findNode(pairNodes.second);
              nodes.insert(node -> getTag());
              mst.addNode(node -> getTag(), node -> getX(), node -> getY());
          }
          mst.addEdge(pairNodes.first, pairNodes.second, itSet -> getWeight());
          itSet++;
          itSet++;
      }
      for (node i:nodeList){
          if (nodes.find(i.getTag()) == nodes.end()){
              nodes.insert(i.getTag());
              mst.addNode(i.getTag(), i.getX(), i.getY());
          }
      }
      return move(mst);
      }

    // Julio
    map <N, int> BFS (N source) {
        if (!findNode(source)) throw "The node does not belong to the graph";
        map <N, int > d;
        N s = source;
        queue<N> cola;
        set<N> used;
        cola.push(s);
        used.insert(s);
        d[s] = 0;
        while (!cola.empty()) {
            N v = cola.front();
            cola.pop();
            for (N u : adjList[v]) {
                if (!used.count(u)) {
                    used.insert(u);
                    cola.push(u);
                    d[u] = d[v] + 1;
                }
            }
        }

        return std::move(d);
    }

    // Julio
    map <N, pair <int, int>> DFS (N source) {
        if (!findNode(source)) throw "The node does not belong to the graph";
        map <N, pair <int, int>> ret;
        map <N, int> time_in;
        map <N, int> time_out;
        map <N, int> color;
        int timer = 0;
        dfsRec(source, time_in, time_out, color, timer);
        for (auto pp: time_in) {
            ret[pp.first] = {time_in[pp.first], time_out[pp.first]};
        }
        return ret;
    }
                          

    // Leonidas
    pair <bool, map <N, bool>> getBipartiteAndColors () {
      const bool BLACK = false;
      const bool WHITE = true;
      map <N, bool> color;
      for (node current: this -> nodeList) {
        N cur_tag = current.getTag();
        queue <N> Q;
        Q.push(cur_tag);
        if (color.count(cur_tag) == 0) {
          color[cur_tag] = BLACK;
        }
        while (not Q.empty()) {
          N u = Q.front();
          Q.pop();
          for (N v: adjList[u]) {
            if (color.count(v) == 0) {
              color[v] = (color[u] == BLACK) ? WHITE : BLACK;
              Q.push(v);
            } else if (color[u] == color[v]) {
              return {false, map <N, bool> ()};
            }
          }
          for (N v: adjList_Trans[u]) {
            if (color.count(v) == 0) {
              color[v] = (color[u] == BLACK) ? WHITE : BLACK;
              Q.push(v);
            } else if (color[u] == color[v]) {
              return {false, map <N, bool> ()};
            }
          }
        }
      }
      return {true, color};
    }

    // Leonidas
    std::pair <int, map <N, int>> getStronglyConnectedComponents () {
      queue <N> topo;
      set <N> vis;
      std::function <void (N)> dfs1 = [&] (int u) -> void {
        vis.insert(u);
        for (N v: adjList[u]) {
          if (vis.count(v)) continue;
          dfs1(v);
        }
        topo.push(u);
      };
      for (node u: nodeList) if (vis.count(u.getTag()) == 0) dfs1(u.getTag());
      set <N> visSCC;
      map <N, int> component;
      int nComponents = 0;
      std::function <void (N)> dfs2 = [&] (int u) -> void {
        visSCC.insert(u);
        component[u] = nComponents;
        for (N v: adjList_Trans[u]) if (visSCC.count(v) == 0) dfs2(v);
      };
      while (not topo.empty()) {
        N u = topo.front();
        topo.pop();
        if (visSCC.count(u)) continue;
        nComponents++;
        dfs2(u);
      }
      return {nComponents, component};
    }

    bool isConvex () { return getStronglyConnectedComponents().first == 1; }
    void setDensityParameter (double density) const { denseParameter = density; }
    int getNumberOfNodes () const { return nodeList.size(); }
    int getNumberOfEdges () const { return edgeList.size(); }
    set <node> getNodeList () const { return nodeList; }
    set <edge> getEdgeList () const { return edgeList; }

    void ImprimirGrafo(){

      cout << "Is directed" << endl;
      cout << is_directed << endl;
      cout << "Imprimiendo nodos" << endl;
      for(auto i:nodeList){
        cout << i.getTag() << " ";
      }
      cout << endl;
      cout << "Imprimiendo aristas" << endl;
      for(auto i:edgeList){
        cout << i.getNodes().first <<" "<< i.getNodes().second<< " "  << i.getWeight() << endl;;
      }
      cout << endl;

      cout << "Imprimiendo la lista de adyacencia" << endl;
      for (auto it = adjList.begin();it != adjList.end();it++){
        cout << it->first<< " ";
        for (auto i: it->second){
          cout << i <<" ";
        }
        cout << endl;
      }

      cout << "Imprimiendo la lista de adyacencia transpuesta" << endl;
      for (auto it = adjList_Trans.begin();it != adjList_Trans.end();it++){
        cout << it->first<< " ";
        for (auto i: it->second){
          cout << i <<" ";
        }
        cout << endl;
      }

    }

private:

    const double denseParameter = 0.5;
    set <node> nodeList;
    set <edge> edgeList;
    map <N, set <N>> adjList;
    map <N, set <N>> adjList_Trans;
    bool is_directed;

    
     void dfsRec(N source, map <N, int>& time_in, map <N, int>& time_out, map <N, int>& color, int& dfs_timer) {
        time_in[source] = dfs_timer++;
        color[source] = 1;
        for (N u : adjList[source])
            if (color[u] == 0)
                dfsRec(u,time_in,time_out,color,dfs_timer);
        color[source] = 2;
        time_out[source] = dfs_timer++;
    }
   
    

};

#endif
