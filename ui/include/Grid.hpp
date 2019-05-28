#ifndef GRID_HPP
#define GRID_HPP

#include <SFML/Graphics.hpp>

class Grid {
  public:
    Grid ();
    ~Grid ();
  private:
    void computeGrid ();
    std::vector <sf::RectangleShape> grid;
};

#endif
