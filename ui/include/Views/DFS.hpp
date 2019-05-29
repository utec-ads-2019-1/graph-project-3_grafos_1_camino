#ifndef DFS_HPP
#define DFS_HPP

#include "View.hpp"

template <typename N, typename E>
class DFS: public View <N, E> {
  public:
    DFS (Graph <N, E>*& graph, std::string label, sf::Font*& font):
      View <N, E> (graph, label, font) {}
    ~DFS () {
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
