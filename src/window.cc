#include "window.hh"
#include <ncurses.h>

void Window::initilize() {
  initscr();
  cbreak();
  noecho();
  clear();
}