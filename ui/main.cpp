#include "UI.hpp"
#include <iostream>
#include <exception>

int main () {
  try {
    UI *ui = new UI();
    ui -> run();
    delete ui;
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}
