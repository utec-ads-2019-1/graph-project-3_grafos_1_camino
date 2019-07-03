#pragma once

#include "View.hpp"

template <typename N, typename E>
class BellmanFord: public View <N, E> {
  public:
    BellmanFord (Graph <N, E>*& graph, std::string label, sf::Font*& font):
      View <N, E> (graph, label, font) {}
    ~BellmanFord () {
      delete this -> console;
    }
    void execute (sf::Font*& font) {
      N source = this -> nodes[this -> indexVertexSelected].getTag();
      this -> state = this -> graph -> BellmandFord(source);
      if (this -> state[0].first.getNumberOfNodes() > 0) {
        this -> console -> add("Negative cycles!!", font, true);
        this -> len++;
      }
      ss = "";
      ss += source;
      this -> computed = true;
      Graph <N, E> g = this -> state[0].first;
      for (int i = 0; i < int(this -> edgesUI.size()); i++) {
        Edge <N, E> e = this -> edges[i];
        if (!g.findEdge(e.getNodes().first, e.getNodes().second) and
            !g.findEdge(e.getNodes().second, e.getNodes().first)) continue;
        Node <N>* from = g.findNode(e.getNodes().first);
        Node <N>* to = g.findNode(e.getNodes().second);
        sf::Vector2f fromPoint(getWindowCoordinates(from -> getX(), from -> getY()));
        sf::Vector2f toPoint(getWindowCoordinates(to -> getX(), to -> getY()));
        this -> edgesUI[i] = buildLine(fromPoint, toPoint, EDGE_MST, EDGE_THICK);
      }
    }
    void update (sf::RenderWindow*& window, const sf::Event& event, sf::Font*& font) {
      if (this -> indexVertexSelected != -1) {
        this -> verticesUI[this -> indexVertexSelected] -> setOutlineThickness(VERTEX_THICK);
        while (this -> console -> getSize() > len) this -> console -> pop();
        if (clicked and not computed) {
          clicked = false;
          execute(font);
        }
        N tag = this -> nodes[this -> indexVertexSelected].getTag();
        if (computed) {
          N tag = this -> nodes[this -> indexVertexSelected].getTag();
          double dis = this -> state[0].second[tag];
          string msg = "dis(" + ss + "," + tag + ")= ";
          char w[100];
          sprintf(w, "%.1f", dis);
          if (std::fabs(dis - this -> graph -> getInfinity()) < 1e-6) {
            msg += "oo";
          } else {
            msg += std::string(w);
          }
          this -> console -> add(msg, font, false);
          this -> indexVertexSelected = -1;
        }
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
    }
  private:
    string ss;
    bool clicked = false;
    bool computed = false;
    int len = 1;
    std::vector <std::pair <Graph <N, E>, std::map <N, double>>> state;

    void clear () {
      for (int i = 0; i < int(this -> nodes.size()); i++) {
        this -> verticesUI[i] -> setFillColor(VERTEX_COLOR);
      }
    }

};
