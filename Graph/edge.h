#ifndef EDGE_H
#define EDGE_H

#include "node.h"

template <typename N, typename E>
class Edge {
  public:
    Node <N>* from = 0;
    Node <N>* to = 0;

    Edge (E data): data(data) {}
    E getData () { return data; }

  private:
    E data;
};

#endif
