#ifndef LOAD_GRAPH_HPP
#define LOAD_GRAPH_HPP

#include <SFML/Graphics.hpp>

class LoadGraph {
  public:
    LoadGraph (sf::Font*& font);
    ~LoadGraph ();
    int update (sf::RenderWindow*& window, const sf::Event& event);
    void draw (sf::RenderWindow*& window);
    int getNumberOfFiles () const;
    std::string getFile (int pos) const;
  private:
    int indexFileSelected = -1;
    std::vector <std::string> files;
    std::vector <sf::RectangleShape*> fileBoxes;
    std::vector <sf::Text*> fileTitle;
};

#endif
