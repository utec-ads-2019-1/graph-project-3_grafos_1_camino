#ifndef GRID_HPP
#define GRID_HPP

#include <SFML/Graphics.hpp>

class Grid {
  public:
    Grid ();
    ~Grid ();
    void draw (sf::RenderWindow*& window);

  private:
    void computeGrid ();
    void computeAxis ();
    void computeVerticalLines ();
    void computeHorizontalLines ();

    std::vector <sf::RectangleShape*> grid;
};

#endif
