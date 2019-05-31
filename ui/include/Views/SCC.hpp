#ifndef SCC_HPP
#define SCC_HPP

#include <map>
#include "View.hpp"

template <typename N, typename E>
class SCC: public View <N, E> {
  public:
    SCC (Graph <N, E>*& graph, std::string label, sf::Font*& font):
      View <N, E> (graph, label, font) {
      std::pair <int, std::map <N, int>> ret = this -> graph -> getStronglyConnectedComponents();
      int nComponents = ret.first;
      components = ret.second;
      std::string msg = std::to_string(nComponents) + " components";
      this -> console -> add(msg, font, false);
      for (int i = 0; i < int(this -> verticesUI.size()); i++) {
        N tag = this -> nodes[i].getTag();
        int colorId = (components[tag]) % int(GRAPH_COLORS.size());
        this -> verticesUI[i] -> setFillColor(GRAPH_COLORS[colorId]);
      }
    }
    ~SCC () {
      delete this -> console;
    }
    void execute (sf::Font*& font) {

    }
    void update (sf::RenderWindow*& window, const sf::Event& event, sf::Font*& font) {
      if (this -> indexVertexSelected != -1) {
        this -> verticesUI[this -> indexVertexSelected] -> setOutlineThickness(VERTEX_THICK);
        while (this -> console -> getSize() > 2) this -> console -> pop();
        N tag = this -> nodes[this -> indexVertexSelected].getTag();
        string msg = "Component " + to_string(this -> components[tag]);
        this -> console -> add(msg, font, false);
        this -> indexVertexSelected = -1;
      }
      for (int i = 0; i < int(this -> nodes.size()); i++) {
        if (this -> verticesUI[i] -> getGlobalBounds().contains(
              window -> mapPixelToCoords(sf::Mouse::getPosition(*window)))) {
          this -> verticesUI[i] -> setOutlineColor(VERTEX_THICK_COLOR);
          this -> verticesUI[i] -> setOutlineThickness(VERTEX_HOVER_THICK);
          this -> indexVertexSelected = i;
        }
      }
    }
    void draw (sf::RenderWindow*& window) {
      this -> drawGraph(window);
      this -> console -> draw(window);
    };
  private:
    std::map <N, int> components;
};

#endif
