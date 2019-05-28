#ifndef EDGE_H
#define EDGE_H

#include <utility>
#include "node.h"

template <typename N, typename E>
class Edge {
  public:
    Edge () {}
    Edge (N from, N to, E weight): from(from), to(to), weight(weight) {}
    E getWeight () { return weight; }
    std::pair <N, N> getNodes () { return {from, to}; }
    bool operator < (const Edge& other) const {
      if (weight != other.weight) return weight < other.weight;
      if (from != other.from) return from < other.from;
      return to < other.to;
    }

  private:
    E weight;
    N from;
    N to;
};

#endif
