class PVector {
  public:
    int x;
    int y;  
    PVector(int x, int y);

    void set(int x, int y);
    float magnitude(PVector vec);
    void add(PVector vec);
    void subtract(PVector vec);
    float magnitude();
    void normalize();
    PVector difference_vector(PVector vec);
};