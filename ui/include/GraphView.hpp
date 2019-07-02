#include <SFML/Graphics.hpp>
#include "./Views/View.hpp"
#include "./Views/DFS.hpp"
#include "./Views/BFS.hpp"
#include "./Views/Prim.hpp"
#include "./Views/Kruskal.hpp"
#include "./Views/Bipartite.hpp"
#include "./Views/SCC.hpp"
#include "./Views/Properties.hpp"
#include "./Views/A_Star.hpp"
#include "./Views/Dijkstra.hpp"
#include "./Views/Floyd_Warshall.hpp"
#include "./Views/Bellman_Ford.hpp"
#include "../../Graph/graph.h"
#include "config.hpp"

template <typename N, typename E>
class GraphView {
  public:
    GraphView () {}
    GraphView (Graph <N, E>*& graph, sf::Font*& font): graph(graph) {
      views.push_back(new DFS <N, E> (graph, "DFS", font));
      views.push_back(new BFS <N, E> (graph, "BFS", font));
      views.push_back(new Prim <N, E> (graph, "Prim", font));
      views.push_back(new Kruskal <N, E> (graph, "Kruskal", font));
      views.push_back(new Bipartite <N, E> (graph, "Bipartite", font));
      views.push_back(new SCC <N, E> (graph, "SCC", font));
      views.push_back(new Properties <N, E> (graph, "Properties", font));
      views.push_back(new A_Star <N, E> (graph, "A*", font));
      views.push_back(new Dijkstra <N, E> (graph, "Dijkstra", font));
      views.push_back(new FloydWarshall <N, E> (graph, "Floyd Warshall", font));
      views.push_back(new BellmanFord <N, E> (graph, "Bellman Ford", font));
    }
    ~GraphView () {
      for (auto* elem: views) delete elem;
      views.clear();
    }
    void update (sf::RenderWindow*& window, const sf::Event& event, sf::Font*& font, int currentView) {
      views[currentView - 1] -> update(window, event, font);
    }
    void draw (sf::RenderWindow*& window, int currentView) {
      views[currentView - 1] -> draw(window);
    }
  private:
    Graph <N, E>* graph;
    std::vector <View <N, E>*> views;

};
