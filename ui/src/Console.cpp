#include "../include/Console.hpp"
#include "../include/config.hpp"

Console::Console (std::string label, sf::Font*& font) {
  currentPosX = CONSOLE_POS_X;
  currentPosY = CONSOLE_POS_Y;
  add(label, font, true);
}

Console::~Console () {
  for (auto* elem: consoleBox) delete elem;
  for (auto* elem: consoleText) delete elem;
  consoleBox.clear();
  consoleText.clear();
}

void Console::draw (sf::RenderWindow*& window) {
  for (auto elem: consoleBox) window -> draw(*elem);
  for (auto elem: consoleText) window -> draw(*elem);
}

void Console::add (std::string text, sf::Font*& font, bool label = false) {
  sf::Vector2f dimentions((label ? 2 : 1) * CONSOLE_WIDTH - CONSOLE_PADDING, CONSOLE_HEIGHT);
  sf::Vector2f position(currentPosX, currentPosY);
  consoleBox.push_back(buildRectangle(dimentions, position,
                                      CONSOLE_COLOR, CHARDS_THICKNESS, true));
  consoleText.push_back(buildText(dimentions, position, text, font));
  currentPosX += (label ? 2 : 1) * CONSOLE_WIDTH;
}

int Console::getSize () { return consoleBox.size(); }

void Console::pop () {
  consoleBox.pop_back();
  consoleText.pop_back();
  currentPosX -= CONSOLE_WIDTH;
}

void Console::clear () {
  while (int(consoleBox.size()) > 1) consoleBox.pop_back();
  while (int(consoleText.size()) > 1) consoleText.pop_back();
  consoleBox.clear();
  consoleText.clear();
  currentPosX = CONSOLE_POS_X;
  currentPosY = CONSOLE_POS_Y + 2 * CONSOLE_WIDTH;
}
