#ifndef VEB_TREE
#define VEB_TREE

#include <vector>

//TODO: templatize the int keys
// Keys and Values
class VebTree {
public:
  VebTree(std::vector<int> keys);

  //should return value later
  int getPredecessor(int key);

private:
  void recursivelyPlace(std::vector<int>& sortedInput,
                        int inputMinIndex,
                        std::vector<int>& tree,
                        int treeMinIndex,
                        int length);

  
  std::vector<int> tree;
}; 


#endif
