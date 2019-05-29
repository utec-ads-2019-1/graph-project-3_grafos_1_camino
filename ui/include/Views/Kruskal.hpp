#ifndef KRUSKAL_HPP
#define KRUSKAL_HPP

#include "View.hpp"

template <typename N, typename E>
class Kruskal: public View <N, E> {
  public:
    Kruskal (Graph <N, E>*& graph, std::string label, sf::Font*& font):
      View <N, E> (graph, label, font) {}
    ~Kruskal () {
      delete this -> console;
    }
    void execute (sf::Font*& font) {
    }
    void draw (sf::RenderWindow*& window) {
      this -> drawGraph(window);
      this -> console -> draw(window);
    };
};

#endif
