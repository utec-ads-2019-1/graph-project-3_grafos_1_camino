#ifndef PRIM_HPP
#define PRIM_HPP

#include "View.hpp"

template <typename N, typename E>
class Prim: public View <N, E> {
  public:
    Prim (Graph <N, E>*& graph, std::string label, sf::Font*& font):
      View <N, E> (graph, label, font) {
      }
    ~Prim () {
      delete this -> console;
    }
    void execute (sf::Font*& font) {
      if (this -> graph -> isDirected()) return;
      N tag = this -> nodes[this -> indexVertexSelected].getTag();
      Graph <N, E> mst = this -> graph -> Prim(tag);
      for (int i = 0; i < int(this -> edgesUI.size()); i++) {
        Edge <N, E> e = this -> edges[i];
        if (!mst.findEdge(e.getNodes().first, e.getNodes().second)) continue;
        Node <N>* from = mst.findNode(e.getNodes().first);
        Node <N>* to = mst.findNode(e.getNodes().second);
        sf::Vector2f fromPoint(getWindowCoordinates(from -> getX(), from -> getY()));
        sf::Vector2f toPoint(getWindowCoordinates(to -> getX(), to -> getY()));
        this -> edgesUI[i] = buildLine(fromPoint, toPoint, EDGE_MST, EDGE_THICK);
      }
    }
    void update (sf::RenderWindow*& window, const sf::Event& event, sf::Font*& font) {
      if (this -> indexVertexSelected != -1) {
        this -> verticesUI[this -> indexVertexSelected] -> setOutlineThickness(VERTEX_THICK);
        while (this -> console -> getSize() > 1) this -> console -> pop();
        if (clicked) {
          clicked = false;
          execute(font);
        }
        N tag = this -> nodes[this -> indexVertexSelected].getTag();
        string msg = "FROM " + this -> tags[this -> indexVertexSelected];
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
      if (event.type == sf::Event::MouseButtonPressed and
          event.mouseButton.button == sf::Mouse::Left) {
        clear();
        clicked = true;
      }
    }
    void draw (sf::RenderWindow*& window) {
      this -> drawGraph(window);
      this -> console -> draw(window);
    };
  private:
    bool clicked = false;

    void clear () {
      for (int i = 0; i < int(this -> edgesUI.size()); i++) {
        Edge <N, E> e = this -> edges[i];
        Node <N>* from = this -> graph -> findNode(e.getNodes().first);
        Node <N>* to = this -> graph -> findNode(e.getNodes().second);
        sf::Vector2f fromPoint(getWindowCoordinates(from -> getX(), from -> getY()));
        sf::Vector2f toPoint(getWindowCoordinates(to -> getX(), to -> getY()));
        this -> edgesUI[i] = buildLine(fromPoint, toPoint, EDGE_COLOR, EDGE_THICK);
      }
    }
};

#endif
