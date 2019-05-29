#include <SFML/Graphics.hpp>
#include "../../Graph/graph.h"

template <typename N, typename E>
class GraphView {
  public:
    GraphView () {}
    GraphView (Graph <N, E>*& graph): graph(graph) {

    }
    ~GraphView () {}
    void update (sf::RenderWindow*& window, int currentView) {

    }
    void draw (sf::RenderWindow*& window, int currentView) {

    }
  private:
    Graph <N, E>* graph;
};
