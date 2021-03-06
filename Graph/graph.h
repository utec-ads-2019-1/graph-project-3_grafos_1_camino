#ifndef GRAPH_H
#define GRAPH_H

#include <algorithm>
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
#include <unordered_map>

using namespace std;

template <typename N, typename E>
class Graph {
  public:
    typedef Graph <N, E> self;
    typedef Node <N> node;
    typedef Edge <N, E> edge;

    Graph (bool is_directed): is_directed(is_directed), negativeWeight(false) {}

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
        if (i -> getTag() == tag) nodeList.erase(i);
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
      if (weight < 0) negativeWeight = true;
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
          node* ret = new node(it_set.getTag(), it_set.getX(), it_set.getY());
          return ret;
        }
      }
      return nullptr;
    }

    // Daniel
    edge* findEdge (N from, N to) {
      for (auto ed : edgeList){
        if(ed.getNodes().first==from and ed.getNodes().second==to){
          edge* ret = new edge(ed.getNodes().first, ed.getNodes().second, ed.getWeight());
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
                //          cout << A << B<< " ";
                auto it2 = currentNodes.find(B);
                if(it2!=currentNodes.end()){
                } else{
                  edge* ed  = findEdge(A,B);
                  availableEdges.push_back(*ed);
                }
              }
              //  cout <<endl;
            }
          }
        }
        if(availableEdges.empty()){
          current = nullptr;
        } else{
          E minW = availableEdges[0].getWeight();
          //cout << "arista disponibles" <<endl;
          for(edge ed: availableEdges){
            // cout << ed.getNodes().first <<ed.getNodes().second << " " << ed.getWeight() << "   ";
            if(minW >ed.getWeight())
              minW = ed.getWeight();
          }
          edge* e;
          for(edge ed: availableEdges){
            if(minW == ed.getWeight()){
              e = &ed;
              break;
            }

          }


          //cout << endl;
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


    // Daniel
    std::vector <std::pair <self, std::map <N, double>>>  A_asterisk(N start,N goal){

      std::vector <std::pair <self, std::map <N, double>>> ret;
      std::map <N, double> dis;
      std::set <edge> visited;
      for (node u: nodeList) dis[u.getTag()] = INF;
      dis[start] = 0;
      auto addGraph = [&] () {
        self g(is_directed);
        for (edge e: visited) {
          node* from = findNode(e.getFrom());
          g.addNode(from -> getTag(), from -> getX(), from -> getY());
          node* to = findNode(e.getTo());
          g.addNode(to -> getTag(), to -> getX(), to -> getY());
          g.addEdge(e.getFrom(), e.getTo(), e.getWeight());
        }
        ret.push_back({g, dis});
      };



      self mst(is_directed);

      std::unordered_map<N, N> parent;
      std::unordered_map<N,double> g_node;
      set<pair<double, N>> f_node;
      f_node.insert({0, start});


      parent[start] = start;
      g_node[start] = 0;

      addGraph();

      while (!f_node.empty()) {
        N current = f_node.begin()->second;
        f_node.erase(f_node.begin());
        if (current == goal) {
          break;
        }
        set<N> neighbors_current = adjList[current];
        for (N next : neighbors_current) {

          edge* e = findEdge(current, next);
          E costo_current_next = findEdge(current,next)->getWeight();
          double g = g_node[current] + costo_current_next;

          if (g_node.find(next) == g_node.end()
              || g < g_node[next]) {
            g_node[next] = g;
            double heuristic = findNode(next)->heuristic(*findNode(goal));
            double f = g + heuristic;
            f_node.insert({f, next});
            dis[next] = g;
            parent[next] = current;
            visited.insert(*e);
            addGraph();
          }

        }
      }

      if(parent.find(goal) == parent.end()) {
        ret.push_back({mst, dis});
        return ret;
      }

      N back = goal;
      node* n = findNode(back);
      mst.addNode(n->getTag(),n->getX(),n->getY());
      while (back != start){
        edge * e = findEdge(parent[back],back);
        back = parent[back];
        n = findNode(back);
        mst.addNode(n->getTag(),n->getX(),n->getY());
        mst.addEdge(e->getNodes().first,e->getNodes().second,e->getWeight());
      }
      ret.push_back({mst, dis});
      return ret;
    }


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
      std::vector <N> topo;
      set <N> vis;
      std::function <void (N)> dfs1 = [&] (int u) -> void {
        vis.insert(u);
        for (N v: adjList[u]) {
          if (vis.count(v)) continue;
          dfs1(v);
        }
        topo.push_back(u);
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
        N u = topo.back();
        topo.pop_back();
        if (visSCC.count(u)) continue;
        nComponents++;
        dfs2(u);
      }
      return {nComponents, component};
    }

    // Leonidas
    std::vector <std::pair <self, std::map <N, double>>> BellmandFord (N source) {
      std::map <N, double> dis;
      std::map <N, N> path;
      for (node u: nodeList) dis[u.getTag()] = INF;
      dis[source] = 0;
      for (int i = 0; i < getNumberOfNodes() - 1; i++) {
        for (edge e: edgeList) {
          if (dis[e.getFrom()] < INF) {
            if (dis[e.getTo()] > dis[e.getFrom()] + e.getWeight()) {
              dis[e.getTo()] = dis[e.getFrom()] + e.getWeight();
              path[e.getTo()] = e.getFrom();
            }
          }
        }
      }
      set <N> node_with_cycle;
      for (edge e: edgeList) {
        if (dis[e.getFrom()] < INF) {
          if (dis[e.getTo()] > dis[e.getFrom()] + e.getWeight()) {
            node_with_cycle.insert(e.getTo());
            path[e.getTo()] = e.getFrom();
          }
        }
      }
      self cycles(is_directed);
      for (N u: node_with_cycle) {
        N cur = u;
        int cnt = 0;
        while (true) {
          N go = path[cur];
          edge* e = findEdge(go, cur);
          node* from = findNode(e -> getFrom());
          cycles.addNode(from -> getTag(), from -> getX(), from -> getY());
          node* to = findNode(e -> getTo());
          cycles.addNode(to -> getTag(), to -> getX(), to -> getY());
          cycles.addEdge(e -> getFrom(), e -> getTo(), e -> getWeight());
          cur = go;
          if (go == u) break;
        }
      }
      std::vector <std::pair <self, std::map <N, double>>> ret;
      ret.push_back({cycles, dis});
      return ret;
    }

    // Julio
    std::pair <std::map <N, std::map <N, double>>, std::map <N, std::map <N, N>>> FloydWarshall () {
      std::map <N, std::map <N, double>> dis;
      std::map <N, std::map <N, N>> path;
      for (node u: nodeList) {
        for (node v: nodeList) {
          dis[u.getTag()][v.getTag()] = INF;
        }
        dis[u.getTag()][u.getTag()] = 0;
      }
      for (edge e: edgeList) {
        dis[e.getFrom()][e.getTo()] = e.getWeight();
        path[e.getFrom()][e.getTo()] = e.getFrom();
      }
      for (node k: nodeList) {
        for (node i: nodeList) {
          for (node j: nodeList) {
            N kk = k.getTag(), ii = i.getTag(), jj = j.getTag();
            if (dis[ii][jj] > dis[ii][kk] + dis[kk][jj]) {
              dis[ii][jj] = dis[ii][kk] + dis[kk][jj];
              path[ii][jj] = kk;
            }
          }
        }
      }
      return {dis, path};
    }

    //Elvis
    int getPosNode (N node) {
      int pos = 0;
      for (auto it : adjList) {
        if (it.first == node) break;
        pos++;
      }
      return pos;
    }

    N getTag (int temp) {
      int count = 0;
      for (auto it : adjList) {
        if (count == temp ) return it.first;
        count++;
      }
    }

    //Elvis
    std::vector <std::pair <self, std::map <N, double>>> Dijkstra (N initialNode, N targetNode) {
      if (negativeWeight) throw "Dijkstra can't apply to this graph: negative weight(s)";
      /*
         std::vector <std::pair <self, std::map <N, double>>> ret;
         std::set <edge> visited;
         std::map <N, double> dis;
         std::map <N, N> path;
         for (node u: nodeList) dis[u.getTag()] = INF;
         std::set <std::pair <double, N>> Q;
         Q.insert({0, initialNode});
         dis[initialNode] = 0;

         auto addGraph = [&] () {
         self g(is_directed);
         for (edge e: visited) {
         node* from = findNode(e.getFrom());
         g.addNode(from -> getTag(), from -> getX(), from -> getY());
         node* to = findNode(e.getTo());
         g.addNode(to -> getTag(), to -> getX(), to -> getY());
         g.addEdge(e.getFrom(), e.getTo(), e.getWeight());
         }
         ret.push_back({g, dis});
         };

         addGraph();

         while (not Q.empty()) {
         N u = (*begin(Q)).second;
         Q.erase(begin(Q));
         if (u == targetNode) break;
         for (N v: adjList[u]) {
         edge* e = findEdge(u, v);
         E w = e -> getWeight();
         addGraph();
         if (dis[v] > dis[u] + w) {
         Q.erase({dis[v], v});
         dis[v] = dis[u] + w;
         path[v] = u;
         Q.insert({dis[v], v});
         visited.insert(*e);
         addGraph();
         }
         }
         }
         self g(is_directed);
         N cur = targetNode;
         while (path.count(cur)) {
         N go = path[cur];
         edge* e = findEdge(go, cur);
         node* from = findNode(e -> getFrom());
         g.addNode(from -> getTag(), from -> getX(), from -> getY());
         node* to = findNode(e -> getTo());
         g.addNode(to -> getTag(), to -> getX(), to -> getY());
         g.addEdge(e -> getFrom(), e -> getTo(), e -> getWeight());
         cur = go;
         }
         ret.push_back({g, dis});
         return ret;
         */


      self dijkstraGraph(is_directed);
      int numNodes = nodeList.size();
      vector <bool> markedNodes(numNodes,false);
      vector <E> lenghtPaths(numNodes, INF);
      vector <N> prevNodes(numNodes, '@');
      int posNode  = getPosNode(initialNode);
      lenghtPaths[posNode] = 0;
      int temp;

      std::vector <std::pair <self, std::map <N, double>>> ret;
      std::set <edge> visited;
      std::map <N, double> dis;
      std::map <N, N> path;
      for (node u: nodeList) dis[u.getTag()] = INF;
      dis[initialNode] = 0;

      auto addGraph = [&] () {
        self g(is_directed);
        for (edge e: visited) {
          node* from = findNode(e.getFrom());
          g.addNode(from -> getTag(), from -> getX(), from -> getY());
          node* to = findNode(e.getTo());
          g.addNode(to -> getTag(), to -> getX(), to -> getY());
          g.addEdge(e.getFrom(), e.getTo(), e.getWeight());
        }
        ret.push_back({g, dis});
      };

      addGraph();

      for (int itNodes = 0; itNodes < numNodes; itNodes++) {
        temp = -1;
        for (int itAdjNodes = 0; itAdjNodes < numNodes; itAdjNodes++) {
          if (!markedNodes[itAdjNodes] && (temp == -1 || lenghtPaths[itAdjNodes] < lenghtPaths[temp])) temp = itAdjNodes;
        }
        if (lenghtPaths[temp] == INF) break;
        markedNodes[temp] = true;
        N tagNode = getTag(temp);
        for (auto itEdge : edgeList) {

          N from = itEdge.getFrom();
          N to = itEdge.getTo();
          pair <N, N > nodes  = itEdge.getNodes();

          if (nodes.first != tagNode) continue;
          N toNode = nodes.second;
          E lenght = itEdge.getWeight();
          int toNodePos = getPosNode(toNode);
          if (lenghtPaths[temp] + lenght < lenghtPaths[toNodePos]) {
            lenghtPaths[toNodePos] = lenghtPaths[temp] + lenght;
            prevNodes[toNodePos] = tagNode;

            // Adding this for the step by step
            dis[to] = lenghtPaths[toNodePos];
            visited.insert(itEdge);
            addGraph();
          }
        }

      }

      N currentNode = targetNode;
      while (currentNode != initialNode) {
        N go = prevNodes[getPosNode(currentNode)];
        node *newNode = findNode(currentNode);
        dijkstraGraph.addNode(newNode -> getTag(), newNode -> getX(), newNode -> getY());
        node*goNode = findNode(go);
        dijkstraGraph.addNode(goNode -> getTag(), goNode -> getX(), goNode -> getY());
        edge *newEdge = findEdge(go, currentNode);
        dijkstraGraph.addEdge(newEdge -> getNodes().first, newEdge -> getNodes().second, newEdge -> getWeight());
        currentNode = go;
      }

      ret.push_back({dijkstraGraph, dis});

      return ret;

    }

    bool isDirected () const { return is_directed; }
    bool isConex () { return getStronglyConnectedComponents().first == 1; }
    void setDensityParameter (double density) const { denseParameter = density; }
    int getNumberOfNodes () const { return nodeList.size(); }
    int getNumberOfEdges () const { return edgeList.size(); }
    set <node> getNodeList () const { return nodeList; }
    set <edge> getEdgeList () const { return edgeList; }
    double getInfinity () const { return INF; }
    bool haveNegativeWeight () const { return negativeWeight; }

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
    const double INF = 1e17;
    bool negativeWeight;

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
