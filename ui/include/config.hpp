#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <SFML/Graphics.hpp>

// WINDOW SETTINGS
const int WIDTH = sf::VideoMode::getDesktopMode().width;
const int HEIGHT = sf::VideoMode::getDesktopMode().height;
const std::string WINDOW_NAME = "Graph";
const float PROGRAM_PADDING = 20.f;

// FONT
const std::string FONT_PATH = "./ui/fonts/arial.ttf";

// MENU
const std::vector <std::string> MENU_OPTIONS = {
  "Load File",
  "DFS",
  "BFS",
  "Prim",
  "Kruskal",
  "SCC",
  "Properties"
};
const float OPTION_WIDTH = 1.0 * (WIDTH - 2 * PROGRAM_PADDING) / 5;
const float OPTION_HEIGHT = 1.0 * (HEIGHT - 2 * PROGRAM_PADDING) / int(MENU_OPTIONS.size());
const float OPTION_PADDING = std::min(OPTION_WIDTH / 10.f, OPTION_HEIGHT / 10.f);
const sf::Color OPTION_COLOR(119, 136, 153); // Light Gray

// GRID
const float CHARDS_THICKNESS = 4;
const float GRID_WIDTH = 4.0 * (WIDTH - 2 * PROGRAM_PADDING) / 5;
const float GRID_HEIGHT = 4.0 * (HEIGHT - 2 * PROGRAM_PADDING) / 5;
const float GRID_POS_X = OPTION_WIDTH + PROGRAM_PADDING;
const float GRID_POS_Y = PROGRAM_PADDING;
const float ORIGIN_X = GRID_POS_X + GRID_WIDTH / 2;
const float ORIGIN_Y = GRID_POS_Y + GRID_HEIGHT / 2;
const int ORIGIN_THICK = 3;
const int NOT_ORIGIN_THICK = 1;
const float GRID_INTERVAL = GRID_HEIGHT / 8;
const float SEGMENT_LENGTH = GRID_INTERVAL / 10;

// CONSOLE
const float CONSOLE_POS_X = GRID_POS_X;
const float CONSOLE_POS_Y = GRID_POS_Y + GRID_HEIGHT + PROGRAM_PADDING;
const float CONSOLE_WIDTH = GRID_WIDTH;
const float CONSOLE_HEIGHT = HEIGHT - CONSOLE_POS_Y - 2 * PROGRAM_PADDING;

// Global variables

sf::RenderWindow window;
sf::Font* font;
sf::Event* event;

sf::RectangleShape drawRect (sf::Vector2f dimentions, sf::Vector2f position, sf::Color background, int thick = 1, bool border = false) {
  sf::RectangleShape box;
  box.setSize(dimentions);
  box.setPosition(position);
  if (border) {
    box.setOutlineThickness(CHARDS_THICKNESS);
    box.setOutlineColor(background);
    box.setFillColor(sf::Color::Black);
  }
  else {
    box.setFillColor(background);
  }
  return box;
}

sf::Text drawText (sf::Vector2f dimentions, sf::Vector2f position, std::string text) {
  sf::Text msg;
  msg.setFont(*font);
  msg.setString(text);
  sf::FloatRect msgDimentions = msg.getLocalBounds();
  double msgW = position.x + (dimentions.x - msgDimentions.width) / 2.0;
  double msgH = position.y + (dimentions.y - msgDimentions.height) / 2.0;
  msg.setPosition(sf::Vector2f(msgW, msgH));
  return msg;
}

#endif
