#ifndef UI_HPP
#define UI_HPP

#include <SFML/Graphics.hpp>
#include <string>

class UI {
  public:
    UI ();
    ~UI ();
    void run ();
  private:
    sf::RenderWindow window;
    sf::Font* font;
    int currentView = 0;

    void handleWindowEvents ();
    void handleUserEvents ();
    void drawMenu ();
    void drawMenuOption (float offset_y, std::string text);
    void drawRect (sf::Vector2f dimentions, sf::Vector2f position, sf::Color background, int thick, bool border);
    void drawText (sf::Vector2f dimentions, sf::Vector2f position, std::string text);
    void drawBox (sf::Vector2f dimentions, sf::Vector2f position, sf::Color background, std::string text);
    void drawGrid ();
    void drawConsole ();
    
};

#endif
