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

    int getDegree (N tag) {
      if (!findNode(tag)) throw "The node doesn't belong to the graph"; 
      if (!is_directed) {
        auto node = adjList.find(tag);
        int degree = node->second.size();
        return degree;
      } else{
        auto node = adjList.find(tag);
        int outDegree = node->second.size();
        node = adjList_Trans.find(tag);
        int inDegree = node->second.size(); 
        }  
    }
    
  private:
    N tag;
    double x;
    double y;
};

#endif
