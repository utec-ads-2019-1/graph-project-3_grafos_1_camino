#include "../include/GraphUI.hpp"
#include "../include/config.hpp"

GraphUI::GraphUI (sf::Font*& font) {
  grid = new Grid();
  loadGraph = new LoadGraph(font);
  for (int i = 0; i < loadGraph -> getNumberOfFiles(); i++) {
    graphFile.push_back(new Graph <char, float> (true));
    loadFromFile <char, float> (loadGraph -> getFile(i), graphFile[i]);
    graphView.push_back(new GraphView <char, float> (graphFile[i], font));
  }
}

GraphUI::~GraphUI () {
  for (auto* elem: graphFile) delete elem;
  for (auto* elem: graphView) delete elem;
  graphFile.clear();
  graphView.clear();
  delete grid;
  delete loadGraph;
}

void GraphUI::update (sf::RenderWindow*& window, const sf::Event& event, sf::Font*& font, int currentView) {
  if (currentView == int(MENU_INDEX::LOAD_FILE)) {
    int index = loadGraph -> update(window, event);
    if (index != -1) {
      currentGraph = index;
    }
  } else {
    graphView[currentGraph] -> update(window, event, font, currentView);
  }
}

void GraphUI::draw (sf::RenderWindow*& window, int currentView) {
  if (currentView == int(MENU_INDEX::LOAD_FILE)) {
    loadGraph -> draw(window);
  } else {
    grid -> draw(window);
    graphView[currentGraph] -> draw(window, currentView);
  }
}
