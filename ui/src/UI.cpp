#include "../include/UI.hpp"
#include "../include/config.hpp"

UI::UI () {
  window = new sf::RenderWindow();
  window -> create(sf::VideoMode(WIDTH, HEIGHT), WINDOW_NAME);
  font = new sf::Font();
  if (not font -> loadFromFile(FONT_PATH)) {
    throw std::runtime_error("Could not load font from " + FONT_PATH + "\n");
  }
  backgroundMusic = new sf::Music(); 
  if (not backgroundMusic -> openFromFile(SOUND_PATH)) {
    throw std::runtime_error("Could not load " + SOUND_PATH + "\n");
}
  menu = new Menu(font);
  graphUI = new GraphUI(font);
  backgroundMusic -> play();
}

UI::~UI () {
  delete font;
  delete backgroundMusic;
  delete window;
  delete menu;
  delete graphUI;
}

void UI::run () {
  while (window -> isOpen()) {
    handleWindowEvents();
    if (not window -> isOpen()) break;
    window -> clear();
    update();
    draw();
    window -> display();
  }
}

void UI::update () {
  graphUI -> update(window, event, font, currentView);
  int currentOption = menu -> update(window);
  if (currentOption != -1) currentView = currentOption;
}

void UI::draw () {
  menu -> draw(window);
  graphUI -> draw(window, currentView);
}

void UI::handleWindowEvents () {
  while (window -> pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window -> close();
    } else if (event.type == sf::Event::KeyPressed and
        event.key.code == sf::Keyboard::Escape) {
      window -> close();
    }
  }
}
