#include "../include/Grid.hpp"
#include "../include/config.hpp"

#include <iostream>

Grid::Grid () {
  computeGrid();
}

Grid::~Grid () {
  for (auto elem: grid) delete elem;
  grid.clear();
}

void Grid::draw (sf::RenderWindow*& window) {
  for (auto elem: grid) window -> draw(*elem);
}

void Grid::computeGrid () {
  computeAxis();
  computeVerticalLines();
  computeHorizontalLines();
}

void Grid::computeAxis () {
  // Border
  grid.push_back(buildRectangle(sf::Vector2f(GRID_WIDTH, GRID_HEIGHT),
                                sf::Vector2f(GRID_POS_X, GRID_POS_Y),
                                OPTION_COLOR, CHARDS_THICKNESS, true));
  // X-axis
  grid.push_back(buildRectangle(sf::Vector2f(GRID_WIDTH, ORIGIN_THICK),
                                sf::Vector2f(GRID_POS_X, ORIGIN_Y),
                                sf::Color::White));
  // Y-axis
  grid.push_back(buildRectangle(sf::Vector2f(ORIGIN_THICK, GRID_HEIGHT),
                                sf::Vector2f(ORIGIN_X, GRID_POS_Y),
                                sf::Color::White));
}

void Grid::computeVerticalLines () {
  // Left Y-axis
  for (double posX = ORIGIN_X - GRID_INTERVAL; posX > GRID_POS_X; posX -= GRID_INTERVAL) {
    for (double posY = GRID_POS_Y; posY + SEGMENT_LENGTH < GRID_POS_Y + GRID_HEIGHT; posY += 2 * SEGMENT_LENGTH) {
      grid.push_back(buildRectangle(sf::Vector2f(NOT_ORIGIN_THICK, SEGMENT_LENGTH),
                                    sf::Vector2f(posX, posY), sf::Color::White));
    }
  }
  // Right Y-axis
  for (double posX = ORIGIN_X + GRID_INTERVAL; posX < GRID_POS_X + GRID_WIDTH; posX += GRID_INTERVAL) {
    for (double posY = GRID_POS_Y; posY + SEGMENT_LENGTH < GRID_POS_Y + GRID_HEIGHT; posY += 2 * SEGMENT_LENGTH) {
      grid.push_back(buildRectangle(sf::Vector2f(NOT_ORIGIN_THICK, SEGMENT_LENGTH),
                                    sf::Vector2f(posX, posY), sf::Color::White));
    }
  }
}

void Grid::computeHorizontalLines () {
  // Up X-axis
  for (double posY = ORIGIN_Y - GRID_INTERVAL; posY > GRID_POS_Y; posY -= GRID_INTERVAL) {
    for (double posX = GRID_POS_X; posX + SEGMENT_LENGTH < GRID_POS_X + GRID_WIDTH; posX += 2 * SEGMENT_LENGTH) {
      grid.push_back(buildRectangle(sf::Vector2f(SEGMENT_LENGTH, NOT_ORIGIN_THICK),
                                    sf::Vector2f(posX, posY), sf::Color::White));
    }
  }
  // Down X-axis
  for (double posY = ORIGIN_Y + GRID_INTERVAL; posY < GRID_POS_Y + GRID_HEIGHT; posY += GRID_INTERVAL) {
    for (double posX = GRID_POS_X; posX + SEGMENT_LENGTH < GRID_POS_X + GRID_WIDTH; posX += 2 * SEGMENT_LENGTH) {
      grid.push_back(buildRectangle(sf::Vector2f(SEGMENT_LENGTH, NOT_ORIGIN_THICK),
                                    sf::Vector2f(posX, posY), sf::Color::White));
    }
  }
}
