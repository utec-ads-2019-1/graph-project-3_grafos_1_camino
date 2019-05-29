#ifndef BIPARTITE_HPP
#define BIPARTITE_HPP

#include "View.hpp"

template <typename N, typename E>
class Bipartite: public View <N, E> {
  public:
    Bipartite (Graph <N, E>*& graph, std::string label, sf::Font*& font):
      View <N, E> (graph, label, font) {}
    ~Bipartite () {
      delete this -> console;
    }
    void update (sf::RenderWindow*& window, const sf::Event& event, sf::Font*& font) {
      
    };
    void draw (sf::RenderWindow*& window) {
      this -> console -> draw(window);
    };
};

#endif
