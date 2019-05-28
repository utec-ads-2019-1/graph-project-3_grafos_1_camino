#include "../include/UI.hpp"
#include "../include/config.hpp"

UI::UI () {
  window.create(sf::VideoMode(WIDTH, HEIGHT), WINDOW_NAME);
  font = new sf::Font();
  if (not font -> loadFromFile(FONT_PATH)) {
    throw std::runtime_error("Could not load font from " + FONT_PATH + "\n");
  }
}

UI::~UI () {}

void UI::run () {
  while (window.isOpen()) {
    handleWindowEvents();
    if (not window.isOpen()) break;
    clear();
    draw();
  }
}

void UI::clear () {
  window.clear();
}

void UI::draw () {
}

void UI::handleWindowEvents () {
  event = new sf::Event();
  while (window.pollEvent(*event)) {
    if (event -> type == sf::Event::Closed) {
      window.close();
    } else if (event -> type == sf::Event::KeyPressed and
        event -> key.code == sf::Keyboard::Escape) {
      window.close();
    }
  }
}

void UI::drawMenu () {
  for (int i = 0; i < int(MENU_OPTIONS.size()); i++) {
    drawMenuOption(OPTION_HEIGHT * i, MENU_OPTIONS[i]);
  }
}

void UI::drawMenuOption (float offset_y, std::string text) {
  sf::Vector2f dimentions(OPTION_WIDTH - 2 * OPTION_PADDING, OPTION_HEIGHT - 2 * OPTION_PADDING);
  sf::Vector2f position(PROGRAM_PADDING + OPTION_PADDING, PROGRAM_PADDING / 2.0 + offset_y + OPTION_PADDING);
  drawBox(dimentions, position, OPTION_COLOR, text);
}


void UI::drawBox (sf::Vector2f dimentions, sf::Vector2f position, sf::Color background, std::string text) {
  drawRect(dimentions, position, background);
  drawText(dimentions, position, text);
}

void UI::drawGrid () {
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

void UI::drawConsole () {
  drawRect(sf::Vector2f(CONSOLE_WIDTH, CONSOLE_HEIGHT), sf::Vector2f(CONSOLE_POS_X, CONSOLE_POS_Y), OPTION_COLOR, CHARDS_THICKNESS, true);
}
