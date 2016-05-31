#ifndef VEB_TREE
#define VEB_TREE

#include <vector>

//TODO: templatize the int keys
// Keys and Values
class VebTree {
public:
  VebTree(std::vector<long> keys);
  ~VebTree();

  //should return value later
  bool contains(long key) const;
  long getPredecessor(long key);

private:
  void recursivelyPlace(std::vector<long>& sortedInput,
                        long inputMinIndex,
                        long * tree,
                        long treeMinIndex,
                        long length);

  bool containsHelper(long key, long index, long order, long& answer, bool isParent=false) const;


  long findSubtree(long key, long index, long order); 
  long * tree;
  long treeOrder;
  long numSegments;
}; 


#endif
