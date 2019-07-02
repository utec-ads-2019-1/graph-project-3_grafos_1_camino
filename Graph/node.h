#ifndef NODE_H
#define NODE_H

template <typename N>
class Node {
  public:
    Node () {};
    Node (N tag, double x, double y): tag(tag), x(x), y(y) {}
    N getTag () const { return tag; }
    double getX () const { return x; }
    double getY () const { return y; }
    bool operator < (const Node& other) const { return tag < other.tag; }
    bool operator == (const Node& other) const { return tag == other.tag; }

    double heuristic (Node goal) const {
        return abs(x - goal.x) + abs( y- goal.y);
    }

  private:
    N tag;
    double x;
    double y;
};

#endif
