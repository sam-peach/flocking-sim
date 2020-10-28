#include "boid.hh"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

Boid::Boid() : position(0, 0), velocity(0, 0) {
  int x, y;
  x = (rand() % COLS);
  y = (rand() % LINES);

  int v_x = (rand() % 3) - 1;
  int v_y = (rand() % 3) - 1;

  position.set(x, y);
  velocity.set(v_x, v_y);
}

void Boid::draw() {
  position.x * 2;
  edge_check();
  mvprintw(position.y, position.x, "@");
}

void Boid::edge_check() {
  if (position.x > COLS) {
    this->position.x = 1;
  } else if (position.x <= 0) {
    this->position.x = COLS;
  } else if (position.y > LINES) {
    this->position.y = 1;
  } else if (position.y <= 0) {
    this->position.y = LINES;
  }
}

void Boid::move() {
  this->velocity.normalize();
  position.add(velocity);
}