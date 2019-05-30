#include "../include/GraphUI.hpp"
#include "../include/config.hpp"

#include <iostream>

GraphUI::GraphUI (sf::Font*& font) {
  grid = new Grid();
  loadGraph = new LoadGraph(font);
  graphFile0 = new Graph <char, int> (true);
  graphView0 = new GraphView <char, int> ();
  graphFile1 = new Graph <char, float> (true);
  graphView1 = new GraphView <char, float> ();
}

GraphUI::~GraphUI () {
  delete grid;
  delete loadGraph;
  delete graphFile0;
  delete graphView0;
  delete graphFile1;
  delete graphView1;
}

void GraphUI::update (sf::RenderWindow*& window, const sf::Event& event, sf::Font*& font, int currentView) {
  if (loading) {
    if (currentGraph == 0) {
      loadFromFile <char, int> ("./ui/input/graph-01.txt", graphFile0, false);
      graphView0 = new GraphView <char, int> (graphFile0, font);
      loading = false;
    }
    if (currentGraph == 1) {
      loadFromFile <char, float> ("./ui/input/graph-02.txt", graphFile1, false);
      graphView1 = new GraphView <char, float> (graphFile1, font);
      loading = false;
    }
  }
  if (currentView == int(MENU_INDEX::LOAD_FILE) or currentView == -1) {
    int index = loadGraph -> update(window, event);
    if (index != -1) {
      currentGraph = index;
      loading = true;
    }
  } else {
    if (currentGraph == 0) graphView0 -> update(window, event, font, currentView);
    if (currentGraph == 1) graphView1 -> update(window, event, font, currentView);
  }
}

void GraphUI::draw (sf::RenderWindow*& window, int currentView) {
  if (currentView == int(MENU_INDEX::LOAD_FILE) or currentView == -1) {
    loadGraph -> draw(window);
  } else {
    grid -> draw(window);
    if (currentGraph == 0) graphView0 -> draw(window, currentView);
    if (currentGraph == 1) graphView1 -> draw(window, currentView);
  }
}
