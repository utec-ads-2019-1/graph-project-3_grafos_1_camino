#ifndef BFS_HPP
#define BFS_HPP

#include <map>
#include "View.hpp"

template <typename N, typename E>
class BFS: public View <N, E> {
  public:
    BFS (Graph <N, E>*& graph, std::string label, sf::Font*& font):
      View <N, E> (graph, label, font) {}
    ~BFS () {
      delete this -> console;
    }
    void execute (sf::Font*& font) {
      this -> levels = this -> graph -> BFS(this -> nodes[this -> indexVertexSelected].getTag());
      for (int i = 0; i < int(this -> nodes.size()); i++) {
        N tag = this -> nodes[i].getTag();
        if (this -> levels.count(tag) == 0) continue;
        int level = this -> levels[tag];
        this -> verticesUI[i] -> setFillColor(GRAPH_COLORS[level % int(GRAPH_COLORS.size())]);
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
        if (this -> levels.count(tag)) {
          string msg = this -> tags[this -> indexVertexSelected] + " level ";
          msg += std::to_string(this -> levels[tag]);
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
    std::map <N, int> levels;
    bool clicked = false;

    void clear () {
      for (int i = 0; i < int(this -> nodes.size()); i++) {
        this -> verticesUI[i] -> setFillColor(VERTEX_COLOR);
      }
    }
};

#endif
