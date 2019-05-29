#ifndef SCC_HPP
#define SCC_HPP

#include "View.hpp"

template <typename N, typename E>
class SCC: public View <N, E> {
  public:
    SCC (Graph <N, E>*& graph, std::string label, sf::Font*& font):
      View <N, E> (graph, label, font) {}
    ~SCC () {
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
