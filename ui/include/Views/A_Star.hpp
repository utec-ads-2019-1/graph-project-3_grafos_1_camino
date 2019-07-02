#pragma once

#include "View.hpp"

template <typename N, typename E>
class A_Star: public View <N, E> {
  public:
    A_Star (Graph <N, E>*& graph, std::string label, sf::Font*& font):
      View <N, E> (graph, label, font) {}
    ~A_Star () {
      delete this -> console;
    }
    void execute (sf::Font*& font) {

    }
    void update (sf::RenderWindow*& window, const sf::Event& event, sf::Font*& font) {

    }
    void draw (sf::RenderWindow*& window) {
      this -> drawGraph(window);
      this -> console -> draw(window);
    }
};
