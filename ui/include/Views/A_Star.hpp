#pragma once

#include "View.hpp"

template <typename N, typename E>
class A_Star : public View <N, E> {
  public:
    A_Star (Graph <N, E>*& graph, std::string label, sf::Font*& font):
      View <N, E> (graph, label, font) {}
    ~A_Star () {
      delete this -> console;
    }
    void execute (sf::Font*& font) {
      this -> state = this -> graph -> A_asterisk(this -> source, this -> target);
      this -> current_index = 0;
      this -> timer = TIMER;
    }
    void update (sf::RenderWindow*& window, const sf::Event& event, sf::Font*& font) {
      if (this -> indexVertexSelected != -1) {
        this -> verticesUI[this -> indexVertexSelected] -> setOutlineThickness(VERTEX_THICK);
        while (this -> console -> getSize() > len) this -> console -> pop();
        if (clicked) {
          clicked = false;
          if (not s_source) {
            this -> source = this -> nodes[this -> indexVertexSelected].getTag();
            this -> ss = "";
            this -> ss += this -> source;
            this -> console -> add("s: " + ss, font, false);
            this -> len++;
            s_source = true;
          }
          if (not s_target and this -> nodes[this -> indexVertexSelected].getTag() != this -> source) {
            this -> target = this -> nodes[this -> indexVertexSelected].getTag();
            this -> tt = "";
            this -> tt += this -> target;
            this -> console -> add("t: " + tt, font, false);
            this -> len++;
            execute(font);
            s_target = true;
          }
        }
        if (not this -> state.empty()) {
          N tag = this -> nodes[this -> indexVertexSelected].getTag();
          double dis = (this -> state)[current_index].second[tag];
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
      if (current_index != -1 and timer < 0 and current_index < this -> state.size()) {
        nextStep(font);
      }
    }
    void draw (sf::RenderWindow*& window) {
      this -> timer--;
      this -> drawGraph(window);
      this -> console -> draw(window);
    }

  private:
    std::vector <std::pair <Graph <N, E>, std::map <N, double>>> state;
    bool clicked;
    N source, target;
    bool s_source = false, s_target = false;
    string ss, tt;
    int len = 1;
    int current_index = -1;
    int timer = TIMER;

    void clear () {
      for (int i = 0; i < int(this -> nodes.size()); i++) {
        this -> verticesUI[i] -> setFillColor(VERTEX_COLOR);
      }
    }

    void clearEdges () {
      
      int i = 0;
      for (auto edge: this -> edges) {
        std::pair <N, N> pp = edge.getNodes();
        Node <N>* from = this -> graph -> findNode(pp.first);
        Node <N>* to = this -> graph -> findNode(pp.second);
        sf::Vector2f fromPoint(getWindowCoordinates(from -> getX(), from -> getY()));
        sf::Vector2f toPoint(getWindowCoordinates(to -> getX(), to -> getY()));
        this -> edgesUI[i] = buildLine(fromPoint, toPoint, EDGE_COLOR, EDGE_THICK);
        i++;
      }

    }

    void nextStep (sf::Font*& font) {
      clearEdges();
      Graph <N, E> g = state[current_index].first;
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
      this -> timer = TIMER;
      if (this -> current_index + 1 < this -> state.size()) this -> current_index++;
    }
};
