#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <SFML/Graphics.hpp>
#include "Grid.hpp"
#include "LoadGraph.hpp"
#include "GraphView.hpp"
#include "../../Graph/graph.h"

class GraphUI {
  public:
    GraphUI (sf::Font*& font);
    ~GraphUI ();
    void update (sf::RenderWindow*& window, const sf::Event& event, sf::Font*& font, int currentView);
    void draw (sf::RenderWindow*& window, int currentView);
  private:
    Grid* grid;
    LoadGraph* loadGraph;
    int currentGraph = -1;
    bool loading = false;
    Graph <char, int>* graphFile0;
    GraphView <char, int>* graphView0;
    Graph <char, float>* graphFile1;
    GraphView <char, float>* graphView1;
};

#endif
