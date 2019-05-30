#ifndef VIEW_HPP
#define VIEW_HPP

#include <type_traits>
#include <SFML/Graphics.hpp>
#include "../../../Graph/graph.h"
#include "../Console.hpp"
#include "../config.hpp"

template <typename N, typename E>
class View {
  public:
    View (Graph <N, E>* graph, std::string label, sf::Font*& font):
      graph(graph),
      console(new Console(label, font)) {
        set <Node <N>> nodeList = graph -> getNodeList();
        set <Edge <N, E>> edgeList = graph -> getEdgeList();
        for (auto vert: nodeList) {
          nodes.push_back(vert);
          if (std::is_same <N, char>::value) {
            std::string curTag = "";
            curTag += vert.getTag();
            tags.push_back(curTag);
          } else {
            tags.push_back(to_string(vert.getTag()));
          }
        }
        for (int i = 0; i < int(nodes.size()); i++) {
          sf::Vector2f position = getWindowCoordinates(nodes[i].getX(), nodes[i].getY());
          verticesUI.push_back(buildCircle(VERTEX_RADIUS,
                position,
                VERTEX_COLOR));
          position.x -= VERTEX_RADIUS;
          position.y -= 2 * VERTEX_RADIUS;
          verticesTextUI.push_back(buildText(sf::Vector2f(2 * VERTEX_RADIUS, 2 * VERTEX_RADIUS),
                position,
                tags[i], font));
          verticesTextUI.back() -> setFillColor(VERTEX_TEXT_COLOR);
        }
        for (auto edge: edgeList) {
          edges.push_back(edge);
          std::pair <N, N> pp = edge.getNodes();
          Node <N>* from = this -> graph -> findNode(pp.first);
          Node <N>* to = this -> graph -> findNode(pp.second);
          sf::Vector2f fromPoint(getWindowCoordinates(from -> getX(), from -> getY()));
          sf::Vector2f toPoint(getWindowCoordinates(to -> getX(), to -> getY()));
          edgesUI.push_back(buildLine(fromPoint, toPoint, EDGE_COLOR, EDGE_THICK));
        }
      }
    void drawGraph (sf::RenderWindow*& window) {
      for (auto elem: edgesUI) window -> draw(elem, 4, sf::Quads);
      for (auto elem: verticesUI) window -> draw(*elem);
      for (auto elem: verticesTextUI) window -> draw(*elem);
    }
    ~View () {
      for (auto* elem: verticesUI) delete elem;
      for (auto* elem: verticesTextUI) delete elem;
      for (auto* elem: edgesUI) delete elem;
      verticesUI.clear();
      verticesTextUI.clear();
      edgesUI.clear();
      tags.clear();
      nodes.clear();
      edges.clear();
    };
    virtual void update (sf::RenderWindow*& window, const sf::Event& event, sf::Font*& font) = 0;
    virtual void execute (sf::Font*& font) = 0;
    virtual void draw (sf::RenderWindow*& window) = 0;
  protected:
    bool toExecute = false;
    int indexVertexSelected = -1;
    Graph <N, E>* graph;
    std::vector <string> tags;
    std::vector <Node <N>> nodes;
    std::vector <Edge <N, E>> edges;
    std::vector <sf::CircleShape*> verticesUI;
    std::vector <sf::Text*> verticesTextUI;
    std::vector <sf::Vertex*> edgesUI;
    Console* console;
};

#endif
