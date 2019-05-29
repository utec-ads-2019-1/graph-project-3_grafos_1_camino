#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
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

    Graph (bool is_directed): is_directed(is_directed) {
    //    cout << "El grafo se creo" << endl;
    }

    ~Graph () {
        // TO DO
    //    cout << "Eliminar lo que se tenga que eliminar" << endl;
    }

    // Elvis
    bool addNode (N tag, double x, double y) {
        if(findNode(tag)) return false;
        cout<<"se va a crear el nodo "<<tag<<endl;
        node newNode = node(tag,x,y);
        set <N> AdjNodes;
        adjList.insert({newNode.getTag(), AdjNodes});
        adjList_Trans.insert({newNode.getTag(), AdjNodes});
        nodeList.insert(newNode);
        cout<<"se creo el nodo"<<endl;
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
        if(findEdge(from,to))
            return false;
        if(from == to)
            return false;
        cout << "se va a crear la arista " << from << " " << to << endl;
        edge newEdge1 =  edge(from,to,weight);
        edgeList.insert(newEdge1);
        cout << "se insertó la arista" << endl;
        auto it = adjList.find(from);
        if (it != adjList.end())
            it->second.insert(to);
        if(is_directed){
            it = adjList_Trans.find(to);
            if (it != adjList.end())
                it->second.insert(from);
        }
        if(!is_directed){
            edge newEdge2 =  edge(to,from,weight);
            edgeList.insert(newEdge2);
            cout << "se va a crear  arista " << to << " " << from << endl;
            auto it = adjList.find(to);
            if (it != adjList.end())
                it->second.insert(from);
            cout << "se inserto la arista"<<endl;

        }

        return true;

    }
        // If is_directed == false -> addEdge(to, from, weight)
        // RETURNS FALSE IF THE VERTEX ALREADY EXISTS


    // Daniel
    bool deleteEdge (N from, N to) {
        if(!findEdge(from,to)){
            cout << "la arista "<<from <<to <<" no está en el grafo" << endl;
            return false;}
        else{
            if(is_directed){
                auto it = adjList.find(from);
                if (it != adjList.end()){
                    auto it2 = (it->second).find(to);
                    (it->second).erase(it2);
                }
                it = adjList_Trans.find(to);
                if (it != adjList_Trans.end()){
                    auto it3 = (it->second).find(from);
                    (it->second).erase(it3);
                }

                edge* del = findEdge(from,to);

                auto itr = edgeList.find(*del);
                edgeList.erase(itr);

            } else{
                auto it = adjList.find(from);
                if (it != adjList.end()){
                    auto it2 = it->second.find(to);
                    it->second.erase(it2);
                }
                it = adjList.find(to);
                if (it != adjList.end()){
                    auto it3 = (it->second).find(from);
                    (it->second).erase(it3);
                }


                edgeList.erase(edgeList.find(*findEdge(from,to)));
                edgeList.erase(edgeList.find(*findEdge(to,from)));



            }
            cout << "arista eliminada" << endl;
            return true;
        }
        // Tener cuidado con actualizar las dependencias
        // Retornar false si el edge no existia

    }

    // Elvis
    node* findNode (N tag) {
        // Retorna un puntero de la ubicacion del vertice `node`
        // retorna NULL si no se encuentra
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
        for (auto i : edgeList){
            if(i.getNodes().first==from and i.getNodes().second==to){
                edge* ret = &i;
                return ret;
            }
        }

        return nullptr;
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
    int getDegree (N tag) { return getOutDegree(tag); }

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

        cout << "Aplicando algoritmo de prim" << endl;
        self mst(is_directed);


        node* current = findNode(tag);
        set <N> currentNodes;

        mst.addNode(current->getTag(),current->getX(),current->getY());
        currentNodes.insert(tag);

        int i = 1;
        while (current){
            vector<edge> availableEdges;
            cout << "iteracion "<< i <<  " de current nodes" << endl;
            for (auto A : currentNodes){
                cout << "current node :" << A << endl;
                for (auto it = adjList.begin();it != adjList.end();it++){
                    if(A == it->first){
                        cout <<"lista de adyacencia de "<< A<<" : " ;
                        for (auto B: it->second){
                            cout  <<  B << " ";
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
                        cout <<endl;
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
    }

    void ImprimirGrafo(){

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

        if(is_directed){
            cout << "Imprimiendo la lista de adyacencia transpuesta" << endl;
            for (auto it = adjList_Trans.begin();it != adjList_Trans.end();it++){
                cout << it->first<< " ";
                for (auto i: it->second){
                    cout << i <<" ";
                }
                cout << endl;
            }
        }


    }

private:

    const double denseParameter = 0.5;
    set <node> nodeList;
    set <edge> edgeList;
    map <N, set <N>> adjList;
    map <N, set <N>> adjList_Trans;
    bool is_directed;
};

#endif
