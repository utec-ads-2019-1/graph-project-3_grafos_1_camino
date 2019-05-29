#ifndef LOAD_GRAPH_HPP
#define LOAD_GRAPH_HPP

#include <SFML/Graphics.hpp>

class LoadGraph {
  public:
    LoadGraph (sf::Font*& font);
    ~LoadGraph ();
    int update (sf::RenderWindow*& window);
    void draw (sf::RenderWindow*& window);
  private:
    int indexFileSelected = -1;
    std::vector <sf::RectangleShape*> fileBoxes;
    std::vector <sf::Text*> fileTitle;
};

#endif
