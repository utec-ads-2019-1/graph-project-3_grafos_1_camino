#ifndef UI_HPP
#define UI_HPP

#include <SFML/Graphics.hpp>
#include "Grid.hpp"
#include "Menu.hpp"
#include "GraphUI.hpp"

class UI {
  public:
    UI ();
    ~UI ();
    void run ();

  private:
    sf::RenderWindow* window;
    sf::Font* font;
    Menu* menu;
    GraphUI* graphUI;
    sf::Event event;
    int currentView = 0;

    void update ();
    void draw ();
    void handleWindowEvents ();

};

#endif
