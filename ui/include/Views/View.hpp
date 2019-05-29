#ifndef VIEW_HPP
#define VIEW_HPP

#include <SFML/Graphics.hpp>
#include "../../../Graph/graph.h"
#include "../Console.hpp"

template <typename N, typename E>
class View {
  public:
    View (Graph <N, E>* graph, std::string label, sf::Font*& font):
      graph(graph), 
      console(new Console(label, font)) {}
    ~View () {};
    virtual void update (sf::RenderWindow*& window, const sf::Event& event, sf::Font*& font) = 0;
    virtual void draw (sf::RenderWindow*& window) = 0;
  protected:
    Graph <N, E>* graph;
    Console* console;
};

#endif
