#ifndef PROPERTIES_HPP
#define PROPERTIES_HPP

#include "View.hpp"

template <typename N, typename E>
class Properties: public View <N, E> {
  public:
    Properties (Graph <N, E>*& graph, std::string label, sf::Font*& font):
      View <N, E> (graph, label, font) {
      bool isConex = this -> graph -> isConex();
      if (isConex) {
        this -> console -> add("conex", font, false);
      } else {
        this -> console -> add("!conex", font, false);
      }
    }
    ~Properties () {
      delete this -> console;
    }
    void execute (sf::Font*& font) {
    }
    void update (sf::RenderWindow*& window, const sf::Event& event, sf::Font*& font) {
      if (this -> indexVertexSelected != -1) {
        this -> verticesUI[this -> indexVertexSelected] -> setOutlineThickness(VERTEX_THICK);
        while (this -> console -> getSize() > 2) this -> console -> pop();
        N tag = this -> nodes[this -> indexVertexSelected].getTag();
        bool isSource = this -> graph -> isSource(tag);
        string msg1 = (isSource) ? "Is source" : "!source";
        bool isSink = this -> graph -> isSink(tag);
        string msg2 = (isSink) ? "Is sink" : "!sink";
        this -> console -> add(msg1, font, false);
        this -> console -> add(msg2, font, false);
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
};

#endif
