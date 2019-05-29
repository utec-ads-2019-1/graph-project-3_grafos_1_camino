#ifndef PROPERTIES_HPP
#define PROPERTIES_HPP

#include "View.hpp"

template <typename N, typename E>
class Properties: public View <N, E> {
  public:
    Properties (Graph <N, E>*& graph, std::string label, sf::Font*& font):
      View <N, E> (graph, label, font) {}
    ~Properties () {
      delete this -> console;
    }
    void update (sf::RenderWindow*& window, const sf::Event& event, sf::Font*& font) {
      
    };
    void draw (sf::RenderWindow*& window) {
      this -> console -> draw(window);
    };
};

#endif
