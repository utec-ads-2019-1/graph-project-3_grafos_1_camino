#include "../include/Menu.hpp"
#include "../include/config.hpp"

Menu::Menu (sf::Font*& font) {
  computeMenu(font);  
}

Menu::~Menu () {
  for (auto elem: menuBoxes) delete elem;
  for (auto elem: menuTitles) delete elem;
  menuBoxes.clear();
  menuTitles.clear();
}

int Menu::update (sf::RenderWindow*& window) {
  if (indexOptionUpdated != -1) {
    menuBoxes[indexOptionUpdated] -> setFillColor(OPTION_COLOR);
    indexOptionUpdated = -1;
  }
  for (int i = 0; i < int(menuBoxes.size()); i++) {
    if (menuBoxes[i] -> getGlobalBounds().contains(
          window -> mapPixelToCoords(sf::Mouse::getPosition(*window)))) {
      menuBoxes[i] -> setFillColor(OPTION_HOVER_COLOR);
      indexOptionUpdated = i;
    }
  }
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) return indexOptionUpdated;
  return -1;
}

void Menu::draw (sf::RenderWindow*& window) {
  for (auto elem: menuBoxes) window -> draw(*elem);
  for (auto elem: menuTitles) window -> draw(*elem);
}

void Menu::computeMenu (sf::Font*& font) {
  for (int i = 0; i < int(MENU_OPTIONS.size()); i++) {
    computeOption(OPTION_HEIGHT * i, MENU_OPTIONS[i], font);
  }
}

void Menu::computeOption (float offset_y, std::string text, sf::Font*& font) {
  sf::Vector2f dimentions(OPTION_WIDTH - 2 * OPTION_PADDING, OPTION_HEIGHT - 2 * OPTION_PADDING);
  sf::Vector2f position(PROGRAM_PADDING + OPTION_PADDING, PROGRAM_PADDING / 2.0 + offset_y + OPTION_PADDING);
  menuBoxes.push_back(buildRectangle(dimentions, position, OPTION_COLOR));
  menuTitles.push_back(buildText(dimentions, position, text, font));
}
