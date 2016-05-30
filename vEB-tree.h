#ifndef VEB_TREE
#define VEB_TREE

#include <vector>

//TODO: templatize the int keys
// Keys and Values
class VebTree {
public:
  VebTree(std::vector<int> keys);

  //should return value later
  bool contains(int key) const;
  int getPredecessor(int key);

private:
  void recursivelyPlace(std::vector<int>& sortedInput,
                        int inputMinIndex,
                        std::vector<int>& tree,
                        int treeMinIndex,
                        int length);

  bool containsHelper(int key, int index, int order, int& answer, bool isParent=false) const;


  int findSubtree(int key, int index, int order); 
  std::vector<int> tree;
  int treeOrder;
  int numSegments;
}; 


#endif
