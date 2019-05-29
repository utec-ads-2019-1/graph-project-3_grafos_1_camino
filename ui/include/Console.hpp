#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <SFML/Graphics.hpp>

class Console {
  public:
    Console (std::string label, sf::Font*& font);
    ~Console ();
    void draw (sf::RenderWindow*& window);
    void add (std::string text, sf::Font*& font, bool label);
    void clear ();
  private:
    std::vector <sf::RectangleShape*> consoleBox;
    std::vector <sf::Text*> consoleText;
    float currentPosX;
    float currentPosY;
};

#endif
