#include "../include/Grid.hpp"
#include "../include/config.hpp"

Grid::Grid () {
  computeGrid();
}

Grid::~Grid () {

}

void Grid::computeGrid () {

}

void Grid::drawGrid () {
  // Border
  drawRect(sf::Vector2f(GRID_WIDTH, GRID_HEIGHT), sf::Vector2f(GRID_POS_X, GRID_POS_Y), OPTION_COLOR, CHARDS_THICKNESS, true);
  // X-axis
  drawRect(sf::Vector2f(GRID_WIDTH, ORIGIN_THICK), sf::Vector2f(GRID_POS_X, ORIGIN_Y), sf::Color::White);
  // Up X-axis
  for (double posY = ORIGIN_Y - GRID_INTERVAL; posY > GRID_POS_Y; posY -= GRID_INTERVAL) {
    for (double posX = GRID_POS_X; posX + SEGMENT_LENGTH < GRID_POS_X + GRID_WIDTH; posX += 2 * SEGMENT_LENGTH) {
      drawRect(sf::Vector2f(SEGMENT_LENGTH, NOT_ORIGIN_THICK), sf::Vector2f(posX, posY), sf::Color::White);
    }
  }
  // Down X-axis
  for (double posY = ORIGIN_Y + GRID_INTERVAL; posY < GRID_POS_Y + GRID_HEIGHT; posY += GRID_INTERVAL) {
    for (double posX = GRID_POS_X; posX + SEGMENT_LENGTH < GRID_POS_X + GRID_WIDTH; posX += 2 * SEGMENT_LENGTH) {
      drawRect(sf::Vector2f(SEGMENT_LENGTH, NOT_ORIGIN_THICK), sf::Vector2f(posX, posY), sf::Color::White);
    }
  }
  // Y-axis
  drawRect(sf::Vector2f(ORIGIN_THICK, GRID_HEIGHT), sf::Vector2f(ORIGIN_X, GRID_POS_Y), sf::Color::White);
  // Left Y-axis
  for (double posX = ORIGIN_X - GRID_INTERVAL; posX > GRID_POS_X; posX -= GRID_INTERVAL) {
    for (double posY = GRID_POS_Y; posY + SEGMENT_LENGTH < GRID_POS_Y + GRID_HEIGHT; posY += 2 * SEGMENT_LENGTH) {
      drawRect(sf::Vector2f(NOT_ORIGIN_THICK, SEGMENT_LENGTH), sf::Vector2f(posX, posY), sf::Color::White);
    }
  }
  // Right Y-axis
  for (double posX = ORIGIN_X + GRID_INTERVAL; posX < GRID_POS_X + GRID_WIDTH; posX += GRID_INTERVAL) {
    for (double posY = GRID_POS_Y; posY + SEGMENT_LENGTH < GRID_POS_Y + GRID_HEIGHT; posY += 2 * SEGMENT_LENGTH) {
      drawRect(sf::Vector2f(NOT_ORIGIN_THICK, SEGMENT_LENGTH), sf::Vector2f(posX, posY), sf::Color::White);
    }
  }
}


