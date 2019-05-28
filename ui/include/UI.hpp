#ifndef UI_HPP
#define UI_HPP

#include <SFML/Graphics.hpp>

class UI {
  public:
    UI ();
    ~UI ();
    void run ();

  private:
    
    void clear ();
    void draw ();
    void handleWindowEvents ();

};

#endif
