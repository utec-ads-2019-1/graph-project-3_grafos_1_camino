#pragma once

#include "View.hpp"

template <typename N, typename E>
class FloydWarshall: public View <N, E> {
  public:
    FloydWarshall (Graph <N, E>*& graph, std::string label, sf::Font*& font):
      View <N, E> (graph, label, font) {
      this -> state = this -> graph -> FloydWarshall();
    }
    ~FloydWarshall () {
      delete this -> console;
    }
    void execute (sf::Font*& font) {
      float dis = this -> state.first[this -> source][this -> target];
      if (std::fabs(dis - this -> graph -> getInfinity()) < 1e-6) return;
      N cur = target;
      Graph <N, E> path_graph(this -> graph -> isDirected());
      auto wa = this -> state.second;
      while (cur != source) {
        N go = this -> state.second[source][cur];
        Edge <N, E>* e = this -> graph -> findEdge(go, cur);
        Node <N>* from = this -> graph -> findNode(e -> getFrom());
        path_graph.addNode(from -> getTag(), from -> getX(), from -> getY());
        Node <N>* to = this -> graph -> findNode(e -> getTo());
        path_graph.addNode(to -> getTag(), to -> getX(), to -> getY());
        path_graph.addEdge(e -> getFrom(), e -> getTo(), e -> getWeight());
        cur = go;
      }
      for (int i = 0; i < int(this -> edgesUI.size()); i++) {
        Edge <N, E> e = this -> edges[i];
        if (!path_graph.findEdge(e.getNodes().first, e.getNodes().second) and
            !path_graph.findEdge(e.getNodes().second, e.getNodes().first)) continue;
        Node <N>* from = path_graph.findNode(e.getNodes().first);
        Node <N>* to = path_graph.findNode(e.getNodes().second);
        sf::Vector2f fromPoint(getWindowCoordinates(from -> getX(), from -> getY()));
        sf::Vector2f toPoint(getWindowCoordinates(to -> getX(), to -> getY()));
        this -> edgesUI[i] = buildLine(fromPoint, toPoint, EDGE_MST, EDGE_THICK);
      }

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
            float dis = this -> state.first[this -> source][this -> target];
            char w[100];
            sprintf(w, "%.1f", dis);
            string msg = "dis: ";
            if (std::fabs(dis - this -> graph -> getInfinity()) < 1e-6) {
              msg += "oo";
            } else {
              msg += std::string(w);
            }
            cout << dis << endl;
            this -> console -> add(msg, font, false);
            this -> len++;
          }
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
    std::pair <std::map <N, std::map <N, double>>, std::map <N, std::map <N, N>>> state; 
    bool clicked;
    N source, target;
    bool s_source = false, s_target = false;
    string ss, tt;
    int len = 1;

    void clear () {
      for (int i = 0; i < int(this -> nodes.size()); i++) {
        this -> verticesUI[i] -> setFillColor(VERTEX_COLOR);
      }
    }

};
