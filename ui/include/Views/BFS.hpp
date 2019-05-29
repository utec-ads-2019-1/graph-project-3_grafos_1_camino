#ifndef BFS_HPP
#define BFS_HPP

#include "View.hpp"

template <typename N, typename E>
class BFS: public View <N, E> {
  public:
    BFS (Graph <N, E>*& graph, std::string label, sf::Font*& font):
      View <N, E> (graph, label, font) {}
    ~BFS () {
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
