#ifndef VEB_TREE
#define VEB_TREE

#include <vector>

//TODO: templatize the int keys
// Keys and Values
class VebTree {
public:
  VebTree(std::vector<double> keys);

  //should return value later
  bool contains(double key);
  double getPredecessor(double key);

private:
  void recursivelyPlace(std::vector<double>& sortedInput,
                        int inputMinIndex,
                        std::vector<double>& tree,
                        int treeMinIndex,
                        int length);

  bool containsHelper(double key, int index, int order, int& answer, bool isParent=false);


  int findSubtree(double key, int index, int order); 
  std::vector<double> tree;
  int treeOrder;
  int numSegments;
}; 


#endif
