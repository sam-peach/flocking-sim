#include "p_vector.hh"

class Boid {
  public:
    Boid();
    PVector position;
    PVector velocity;

    void draw();
    void move();
  private:
    void edge_check();
};