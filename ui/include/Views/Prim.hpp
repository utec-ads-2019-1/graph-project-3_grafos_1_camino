#ifndef PRIM_HPP
#define PRIM_HPP

#include "View.hpp"

template <typename N, typename E>
class Prim: public View <N, E> {
  public:
    Prim (Graph <N, E>*& graph, std::string label, sf::Font*& font):
      View <N, E> (graph, label, font) {}
    ~Prim () {
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
