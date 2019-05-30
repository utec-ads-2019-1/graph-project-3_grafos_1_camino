#ifndef KRUSKAL_HPP
#define KRUSKAL_HPP

#include <set>
#include "View.hpp"

template <typename N, typename E>
class Kruskal: public View <N, E> {
  public:
    Kruskal (Graph <N, E>*& graph, std::string label, sf::Font*& font):
      View <N, E> (graph, label, font) {
      Graph <N, E> mst = this -> graph -> Kruskal();
      for (int i = 0; i < int(this -> edgesUI.size()); i++) {
        Edge <N, E> e = this -> edges[i];
        Node <N>* from = mst.findNode(e.getNodes().first);
        Node <N>* to = mst.findNode(e.getNodes().second);
        sf::Vector2f fromPoint(getWindowCoordinates(from -> getX(), from -> getY()));
        sf::Vector2f toPoint(getWindowCoordinates(to -> getX(), to -> getY()));
        this -> edgesUI[i] = buildLine(fromPoint, toPoint, EDGE_MST, EDGE_THICK);
      }
    }
    ~Kruskal () {
      delete this -> console;
    }
    void execute (sf::Font*& font) {
    }
    void update (sf::RenderWindow*& window, const sf::Event& event, sf::Font*& font) {
      if (this -> indexVertexSelected != -1) {
        this -> verticesUI[this -> indexVertexSelected] -> setOutlineThickness(VERTEX_THICK);
        while (this -> console -> getSize() > 2) this -> console -> pop();
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
