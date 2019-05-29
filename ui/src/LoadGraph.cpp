#include <sys/types.h>
#include <dirent.h>
#include "../include/LoadGraph.hpp"
#include "../include/config.hpp"

#include <iostream>

LoadGraph::LoadGraph (sf::Font*& font) {

  std::vector <std::string> files;
  std::string path = "./ui/input/";
  DIR* dir = opendir(path.c_str());
  struct dirent *dp;
  while ((dp = readdir(dir)) != NULL) {
    if (dp -> d_name[0] != '.') files.push_back(dp -> d_name);
  }
  closedir(dir);

  int index = 0;
  for (float posY = GRID_POS_Y; posY < GRID_POS_Y + GRID_HEIGHT; posY += GRID_INTERVAL) {
    if (index == int(files.size())) break;
    sf::Vector2f dimentions(GRID_WIDTH, GRID_INTERVAL - FILE_PADDING);
    sf::Vector2f position(GRID_POS_X, posY);
    fileBoxes.push_back(buildRectangle(dimentions, position, FILE_COLOR));
    fileTitle.push_back(buildText(dimentions, position, files[index], font));
    index++;
  }
}

LoadGraph::~LoadGraph () {
  for (auto* elem: fileBoxes) delete elem;
  for (auto* elem: fileTitle) delete elem;
  fileBoxes.clear();
  fileTitle.clear();
}

int LoadGraph::update (sf::RenderWindow*& window) {
  if (indexFileSelected != -1) {
    fileBoxes[indexFileSelected] ->  setFillColor(FILE_COLOR);
    indexFileSelected = -1;
  };
  for (int i = 0; i < int(fileBoxes.size()); i++) {
    if (fileBoxes[i] -> getGlobalBounds().contains(
          window -> mapPixelToCoords(sf::Mouse::getPosition(*window)))) {
      fileBoxes[i] -> setFillColor(OPTION_HOVER_COLOR);
      indexFileSelected = i;
    }
  }
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) return indexFileSelected;
  return -1;
}

void LoadGraph::draw (sf::RenderWindow*& window) {
  for (auto elem: fileBoxes) window -> draw(*elem);
  for (auto elem: fileTitle) window -> draw(*elem);
}


