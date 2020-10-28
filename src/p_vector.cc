#include "p_vector.hh"
#include <ncurses.h>
#include <math.h>

PVector::PVector(int x, int y) {
  this->x = x;
  this->y = y;
}

void PVector::set(int x, int y) {
  this->x = x;
  this->y = y;
}

void PVector::add(PVector vec) {
  this->x += vec.x;
  this->y += vec.y;
}

void PVector::subtract(PVector vec) {
  this->x -= (vec.x);
  this->y -= (vec.y);
}

PVector PVector::difference_vector(PVector vec) {
  int x = abs(this->x - vec.x);
  int y = abs(this->y - vec.y);

  PVector diff(x, y);
  return diff;
} 

float PVector::magnitude() {
  float mag = sqrt( pow(this->x, 2) + pow(this->y, 2) );

  return mag;
}

void PVector::normalize() {
  float mag = this-> magnitude();
  if (mag > 4) {
    this->set( (this->x * 0.5), (this->y * 0.5));
  }
}