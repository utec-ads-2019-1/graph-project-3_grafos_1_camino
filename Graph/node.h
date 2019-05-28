#ifndef NODE_H
#define NODE_H

template <typename N>
class Node {
  public:
    Node () {};
    Node (N tag, double x, double y): tag(tag), x(x), y(y) {}
    N getTag () { return tag; }
    double getX () { return x; }
    double getY () { return y; }
    bool operator < (const Node& other) const { return tag < other.tag; }

  private:
    N tag;
    double x;
    double y;
};

#endif
