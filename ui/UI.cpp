// Version hardcodeo
// La modularizacion para el siguiente entregable

#include "UI.hpp"
#include <vector>

#include <iostream>

// CONSTANT VALUES

// WINDOW SETTINGS
const int WIDTH = sf::VideoMode::getDesktopMode().width;
const int HEIGHT = sf::VideoMode::getDesktopMode().height;
const std::string WINDOW_NAME = "Graph";
const float programPadding = 20.f;

// FONT
const std::string FONT_PATH = "./ui/fonts/arial.ttf";

// MENU
const std::vector <std::string> menuOptions = {
  "Load File",
  "DFS",
  "BFS",
  "Prim",
  "Kruskal",
  "SCC",
  "Properties"
};
const float optionWidth = 1.0 * (WIDTH - 2 * programPadding) / 5;
const float optionHeight = 1.0 * (HEIGHT - 2 * programPadding) / int(menuOptions.size());
const float optionPadding = std::min(optionWidth / 10.f, optionHeight / 10.f);
const sf::Color optionColor(119, 136, 153); // Light Gray

// GRID
const float CHARDS_THICKNESS = 4;
const float gridWidth = 4.0 * (WIDTH - 2 * programPadding) / 5;
const float gridHeight = 4.0 * (HEIGHT - 2 * programPadding) / 5;
const float gridPosX = optionWidth + programPadding;
const float gridPosY = programPadding;
const float originX = gridPosX + gridWidth / 2;
const float originY = gridPosY + gridHeight / 2;
const int originThick = 3;
const int notOriginThick = 1;
const float gridInterval = gridHeight / 8;
const float segmentLength = gridInterval / 10;

// CONSOLE
const float consolePosX = gridPosX;
const float consolePosY = gridPosY + gridHeight + programPadding;
const float consoleWidth = gridWidth;
const float consoleHeight = HEIGHT - consolePosY - 2 * programPadding;


UI::UI (): window(sf::VideoMode(WIDTH, HEIGHT), WINDOW_NAME) {
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
    window.clear();
    drawMenu();
    drawGrid();
    drawConsole();
    handleUserEvents();
    window.display();
  }
}

void UI::handleWindowEvents () {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window.close();
    } else if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Escape) {
      window.close();
    }
  }
}

void UI::handleUserEvents () {
  // TO DO
}

void UI::drawMenu () {
  for (int i = 0; i < int(menuOptions.size()); i++) {
    drawMenuOption(optionHeight * i, menuOptions[i]);
  }
}

void UI::drawMenuOption (float offset_y, std::string text) {
  sf::Vector2f dimentions(optionWidth - 2 * optionPadding, optionHeight - 2 * optionPadding);
  sf::Vector2f position(programPadding + optionPadding, programPadding / 2.0 + offset_y + optionPadding);
  drawBox(dimentions, position, optionColor, text);
}

void UI::drawRect (sf::Vector2f dimentions, sf::Vector2f position, sf::Color background, int thick = 1, bool border = false) {
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
  window.draw(box);
}
void UI::drawText (sf::Vector2f dimentions, sf::Vector2f position, std::string text) {
  sf::Text msg;
  msg.setFont(*font);
  msg.setString(text);
  sf::FloatRect msgDimentions = msg.getLocalBounds();
  double msgW = position.x + (dimentions.x - msgDimentions.width) / 2.0;
  double msgH = position.y + (dimentions.y - msgDimentions.height) / 2.0;
  msg.setPosition(sf::Vector2f(msgW, msgH));
  window.draw(msg);
}

void UI::drawBox (sf::Vector2f dimentions, sf::Vector2f position, sf::Color background, std::string text) {
  drawRect(dimentions, position, background);
  drawText(dimentions, position, text);
}

void UI::drawGrid () {
  // Border
  drawRect(sf::Vector2f(gridWidth, gridHeight), sf::Vector2f(gridPosX, gridPosY), optionColor, CHARDS_THICKNESS, true);
  // X-axis
  drawRect(sf::Vector2f(gridWidth, originThick), sf::Vector2f(gridPosX, originY), sf::Color::White);
  // Up X-axis
  for (double posY = originY - gridInterval; posY > gridPosY; posY -= gridInterval) {
    for (double posX = gridPosX; posX + segmentLength < gridPosX + gridWidth; posX += 2 * segmentLength) {
      drawRect(sf::Vector2f(segmentLength, notOriginThick), sf::Vector2f(posX, posY), sf::Color::White);
    }
  }
  // Down X-axis
  for (double posY = originY + gridInterval; posY < gridPosY + gridHeight; posY += gridInterval) {
    for (double posX = gridPosX; posX + segmentLength < gridPosX + gridWidth; posX += 2 * segmentLength) {
      drawRect(sf::Vector2f(segmentLength, notOriginThick), sf::Vector2f(posX, posY), sf::Color::White);
    }
  }
  // Y-axis
  drawRect(sf::Vector2f(originThick, gridHeight), sf::Vector2f(originX, gridPosY), sf::Color::White);
  // Left Y-axis
  for (double posX = originX - gridInterval; posX > gridPosX; posX -= gridInterval) {
    for (double posY = gridPosY; posY + segmentLength < gridPosY + gridHeight; posY += 2 * segmentLength) {
      drawRect(sf::Vector2f(notOriginThick, segmentLength), sf::Vector2f(posX, posY), sf::Color::White);
    }
  }
  // Right Y-axis
  for (double posX = originX + gridInterval; posX < gridPosX + gridWidth; posX += gridInterval) {
    for (double posY = gridPosY; posY + segmentLength < gridPosY + gridHeight; posY += 2 * segmentLength) {
      drawRect(sf::Vector2f(notOriginThick, segmentLength), sf::Vector2f(posX, posY), sf::Color::White);
    }
  }
}

void UI::drawConsole () {
  drawRect(sf::Vector2f(consoleWidth, consoleHeight), sf::Vector2f(consolePosX, consolePosY), optionColor, CHARDS_THICKNESS, true);
}
