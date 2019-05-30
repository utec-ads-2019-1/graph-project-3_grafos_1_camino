#ifndef MENU_HPP 
#define MENU_HPP

#include <SFML/Graphics.hpp>

class Menu {
  public:
    Menu (sf::Font*& font);
    ~Menu ();
    int update (sf::RenderWindow*& window);
    void draw (sf::RenderWindow*& window);

  private:
    void computeMenu (sf::Font*& font);
    void computeOption (float offset_y, std::string text, sf::Font*& font);
    int indexOptionUpdated = -1;

    std::vector <sf::RectangleShape*> menuBoxes;
    std::vector <sf::Text*> menuTitles;
};

#endif
