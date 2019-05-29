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
    void execute (sf::Font*& font) {
      this -> console -> clear();
      pair <bool, map <N, bool>> res = this -> graph -> getBipartiteAndColors();
      if (not res.first) {
        this -> console -> add("!Bipartite", font, false);
      } else {
        this -> console -> add("Bipartite", font, false);
      }
      for (int i = 0; i < int(this -> verticesUI.size()); i++) {
        this -> verticesUI[i] -> setFillColor(GRAPH_COLORS[res.second[this -> nodes[i].getTag()]]);
      }
      this -> toExecute = false;
    }
    void draw (sf::RenderWindow*& window) {
      this -> drawGraph(window);
      this -> console -> draw(window);
    };
};

#endif
