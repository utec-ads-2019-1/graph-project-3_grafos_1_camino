#include <iostream>
#include <exception>
#include "../include/UI.hpp"

int main () {
  try {
    UI* ui = new UI();
    ui -> run();
    delete ui;
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}
