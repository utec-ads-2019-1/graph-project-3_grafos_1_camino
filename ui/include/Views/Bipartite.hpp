#ifndef BIPARTITE_HPP
#define BIPARTITE_HPP

#include "View.hpp"

template <typename N, typename E>
class Bipartite: public View <N, E> {
  public:
    Bipartite (Graph <N, E>*& graph, std::string label, sf::Font*& font):
      View <N, E> (graph, label, font) {
      this -> execute(font);  
    }
    ~Bipartite () {
      delete this -> console;
    }
    void execute (sf::Font*& font) {
      this -> res = this -> graph -> getBipartiteAndColors();
      if (not this -> res.first) {
        this -> console -> add("Not bipartite", font, false);
      } else {
        this -> console -> add("Is bipartite", font, false);
        for (int i = 0; i < int(this -> verticesUI.size()); i++) {
          this -> verticesUI[i] -> setFillColor(GRAPH_COLORS[this -> res.second[this -> nodes[i].getTag()]]);
        }
      }
    }

    void update (sf::RenderWindow*& window, const sf::Event& event, sf::Font*& font) {
      if (this -> indexVertexSelected != -1) {
        while (this -> console -> getSize() > 2) this -> console -> pop();
        string msg = this -> tags[this -> indexVertexSelected] + " color ";
        msg += ('0' + this -> res.second[this -> nodes[this -> indexVertexSelected].getTag()]);
        this -> console -> add(msg, font, false);
        this -> indexVertexSelected = -1;
      }
      for (int i = 0; i < int(this -> nodes.size()); i++) {
        if (this -> verticesUI[i] -> getGlobalBounds().contains(
              window -> mapPixelToCoords(sf::Mouse::getPosition(*window)))) {
          this -> indexVertexSelected = i;
        }
      }
    }
    void draw (sf::RenderWindow*& window) {
      this -> drawGraph(window);
      this -> console -> draw(window);
    };
  private:
    pair <bool, map <N, bool>> res;
};

#endif
