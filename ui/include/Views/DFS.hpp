#ifndef DFS_HPP
#define DFS_HPP

#include <map>
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
      this -> times = this -> graph -> DFS(this -> nodes[this -> indexVertexSelected].getTag());
      for (int i = 0; i < int(this -> nodes.size()); i++) {
        N tag = this -> nodes[i].getTag();
        if (this -> times.count(tag) == 0) continue;
        int time_in = this -> times[tag].first;
        this -> verticesUI[i] -> setFillColor(GRAPH_COLORS[time_in % int(GRAPH_COLORS.size())]);
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
        if (this -> times.count(tag)) {
          string msg = this -> tags[this -> indexVertexSelected] + " -> ";
          msg += "(" + std::to_string(this -> times[tag].first) + ", ";
          msg += std::to_string(this -> times[tag].second) + ")";
          this -> console -> add(msg, font, false);
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
    };
  private:
    std::map <N, pair <int, int>> times;
    bool clicked = false;

    void clear () {
      for (int i = 0; i < int(this -> nodes.size()); i++) {
        this -> verticesUI[i] -> setFillColor(VERTEX_COLOR);
      }
    }

};

#endif
