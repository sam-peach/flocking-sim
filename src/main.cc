#include "window.hh"
#include "boid.hh"
#include <math.h>
#include <ncurses.h>
#include <chrono>
#include <thread>
#include <time.h>

PVector rule_1(Boid& b, Boid boids[], int len);
PVector rule_2(Boid& b, Boid boids[], int len);
PVector rule_3(Boid& b, Boid boids[], int len);
void draw_circle(float &t);

int main() {  
  srand(time(NULL));

  Window win;
  win.initilize();

  Boid boids[100];

  int len = sizeof(boids)/sizeof(boids[0]);
  while(true) {
    clear();  
    // mvprintw((LINES / 2), (COLS / 2), "##");

    for (int i = 0; i < len; i++) {
      Boid& b = boids[i];

      PVector v1 = rule_1(b, boids, len);
      PVector v2 = rule_2(b, boids, len);
      PVector v3 = rule_3(b, boids, len);

      PVector new_velocity(0, 0);
      new_velocity.add(v1);
      new_velocity.add(v2);  
      new_velocity.add(v3);

      new_velocity.x *= 2.5; 

      b.velocity.add(new_velocity);
      b.move();
      b.draw();
    }
    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(120));

  }

  return 0;
}

void draw_circle(float &t) {
  int r = 8;
  int x = COLS/2 + (cos(t) * (r * 2.5) );
  int y = LINES/2 + (sin(t) * r);

  mvprintw(y, x, "@");

  t+= 0.5;
}

PVector rule_1(Boid& b, Boid boids[], int len) {
  PVector p_center(0, 0);
  PVector c((COLS / 2), (LINES / 2));

  for (int i = 0; i < len; i++) {
    if (&b != &boids[i]) {
      p_center.add(boids[i].position);
    }
  }

  p_center.x /= (len - 1);
  p_center.y /= (len - 1);

  p_center.subtract(b.position);

  c.subtract(b.position);
  c.normalize();

  p_center.add(c);

  p_center.x /= 2;
  p_center.y /= 2;

  p_center.x *= 0.1;
  p_center.y *= 0.1;
  
  return p_center;
}

PVector rule_2(Boid& b, Boid boids[], int len) {
  PVector c(0, 0);
  int r = 5 ;
  for (int i = 0; i < len; i++) {
    if (&b != &boids[i]) {
      int pos_diff_x = b.position.x - boids[i].position.x; 
      int pos_diff_y = b.position.y - boids[i].position.y; 
      if( sqrt( pow(abs(pos_diff_x), 2) + pow(abs(pos_diff_y), 2) ) < r) {
        PVector d(pos_diff_x, pos_diff_y);
        c.subtract(d);
      }
    }
  }

  c.normalize();
  return c;
}

PVector rule_3(Boid& b, Boid boids[], int len) {
  PVector v(0, 0);

  for (int i = 0; i < len; i++) {
    if (&b != &boids[i]) {
      v.add(boids[i].velocity);
    }
  }

  v.x /= (len -1);
  v.y /= (len -1);

  v.subtract(b.velocity);

  v.x /= 8;
  v.y /= 8;

  return v;
}