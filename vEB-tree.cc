#include "vEB-tree.h"
#include "math.h"
#include <limits.h>
#include <iostream>
#include "assert.h"
using namespace std;

// For quickly converting from order to the size of that perfect tree.
// Can also be computed as ((1 << (1 << order) ) - 1)
// Can go the opposite direction with (ceil(log2(ceil(log2(size + 1)))))
static unsigned orderToSize[] = {1, 3, 15, 255, 65535, 4294967295};

VebTree::VebTree(std::vector<int> keys){
  //tree = vector<int>(keys.size()); // This will order the vals into a tree
  if (keys.size() < 2) {
    cout << "Cannot create a vEB tree of size < 2. Exiting..." << endl;
    exit(-1);
  }
  treeOrder = (int) ceil(log2(ceil(log2(keys.size() + 1))));

  int sizeB = (1 << (1 << (treeOrder -1))) - 1;
  int nSeg = (keys.size() - 1) / sizeB;
  numSegments = nSeg;
  int nTop = keys.size() - (nSeg * sizeB);

  tree = vector<int>(keys.size() - nTop + sizeB);
  vector<int> topElems;
  int currIndex = sizeB; // Reserve the first block for our top tree
  int inputIndex = 0;
  for (int i = 0; i < nSeg; i++) {
    recursivelyPlace(keys, inputIndex /*i * (sizeB + 1)*/, tree, currIndex, sizeB);
    currIndex += sizeB;
    inputIndex += sizeB;
    if (inputIndex < keys.size()) {
      topElems.push_back(keys.at(inputIndex));
       inputIndex++;
     // tree[i] = keys[((i+1) * (sizeB + 1))-1];
    }
  }
  while (inputIndex < keys.size()) {
    topElems.push_back(keys.at(inputIndex));
    inputIndex++;
  }
  while(topElems.size() < sizeB) {
    topElems.push_back(INT_MAX);
  }

  recursivelyPlace(topElems, 0, tree, 0, sizeB);
  /*int counter = 0;
  for (int x : tree) {
    counter++;
    cout << counter << ":  " << x << endl;
  }
  */
}

// These are the perfect subtree sizes, up to a large number.
// Just used for sanity checking.
bool isPerfectSubTreeSize(int size) {
  return size == 1 || size == 3 || size == 15 || size == 255 || size == 65535;
}

void VebTree::recursivelyPlace(vector<int>& sortedInput,
                                int inputMinIndex,
                                vector<int>& tree,
                                int treeMinIndex, 
                                int size) {
  // NOTE: range is [minIndex, maxIndex), exclusing the maxIndex
  // We want to take the inputs in this range of the inputs, and store them
  // in this (other) range in the tree array
  if (inputMinIndex >= sortedInput.size()) {
    cout << "RECURSIVE PLACE WAS WEIRD" << endl;
    assert(false);
    return;
  } 
  if (!isPerfectSubTreeSize(size)) {
    cout << "Attempted to recursively place a tree of size " << size << endl;
    exit(1);
  }
  if (size == 1) {// Base case! size one is easy
    tree.at(treeMinIndex) = sortedInput.at(inputMinIndex);
    return;
  }
  int subTreeSize = sqrt(size + 1) - 1;
  int numChildren = (size / subTreeSize) - 1;
  // Reserve the first segment spot for the top tree
  int currIndex = treeMinIndex + subTreeSize;
  // Remember the elems for the top tree as we go
  vector<int> topElems;
  for (int child = 0; child < numChildren; child++) {
    recursivelyPlace(sortedInput, inputMinIndex + (child * (subTreeSize + 1)),
                     tree, currIndex,
                     subTreeSize);
    
    currIndex += subTreeSize;
    if (child != numChildren - 1) {
      // Not the last child? Then this next elem belongs in the top
      topElems.push_back(sortedInput.at(inputMinIndex +
                                     ((child+1) * (subTreeSize + 1))-1));
    }
  }

  // All the bottom trees have been placed. Now add the topElems into the space
  // we reserved earlier
  recursivelyPlace(topElems, 0, tree, treeMinIndex, subTreeSize);
}
  

int VebTree::getPredecessor(int key) {
  return -1.0; 
}



/* This method functionally has 2 return values: The boolean indicates whether
 * or not the key was present in this subtree. If it was present, then the
 * returnAnswer int is updated to be the in-order index of that node in this
 * subtree.
 *
 * If it wasn't found, then returnAnswer is updated to be the index of the
 * subtree that might contain this key.
 *
 * Say you has a subtree of order 1 (just 3 nodes) like this:
 *
 *                  10
 *                /    \
 *               5      15
 *
 * If you searched for 5, it would return true and set the int to 0.
 *
 * If you search for 3, it would return false and set the int to 0 (since 3
 * would be in the leftmost of the 4 subtrees that could be hanngin off this
 * tree.
 *
 * If you search for 12, it would return false and set the int to 2, since it
 * would be in the 3rd subtree hanging off this subtree. (The one to the left
 * of 15).
 *
 * It does this by first recursively checking the top-structure of this tree,
 * (in this example, the order 0 tree that has one node: 10) and returns if 
 * it found it.
 * 
 * If the node wasn't in the top, then it uses the answer from the top query
 * to index into one of the bottom trees (here we have two: the tree with 5
 * and the tree with 15) and search for it there.
 * 
 * If it is found in the bottom tree, then we return true and set the int
 * accordingly (keeping track of the number of nodes in the top and bottom
 * that were smaller than this node).
 *
 * If it wasn't in the bottom tree, then we calculate which subtree it would be
 * in, and return false.
 */
bool VebTree::containsHelper(int key, int index, int order, int& returnAnswer,
                             bool isParent) const {
  if (index < 0 || index > tree.size()) {
    //cout << "Hit the weird base case in contains..." << endl;
    //cout << "Searching for " << key << endl;
    assert(false);
  }
  if (order == 0) {
    if (key == tree.at(index)) {
      // Found the answer. Report that the key was in the 0th child
      returnAnswer = 0;
      return true;
    } else { 
      // Not found, say if we're in the 0th (left) or 1th (right) subtree
      if (key < tree.at(index)) returnAnswer = 0;
      else                      returnAnswer = 1;
      return false;
    }
  }
  int topAns;
  int sizeOfChild = orderToSize[order -1];
  if (containsHelper(key, index, order - 1, topAns)) {
    // Found the index in our top structure, report which node it was in
    int numSmallerChildren = topAns + 1;
    returnAnswer = topAns + (sizeOfChild * numSmallerChildren);
    return true;
  } else {
    // Not found in the top, ans is the index of the child to check
    // skip sizeOfChild indices to get past top, then skip sizeOfChild
    // for each child to skip.
    int indexOfChild = index + (sizeOfChild *(topAns + 1));
    if (isParent) {
      // We have an unusual number of children. Make sure this
      // one is valid
      if (topAns >= numSegments) {
        //TODO: Do I need to set returnAnswer?
        return false;               
      }
    }
    int childAns;
    if (containsHelper(key, indexOfChild, order -1, childAns)) {
      // Found in the bottom tree, report which node we found it in

      // We have topAns full bottom trees, and topAns nodes in the top struct
      // that are less than this node.
      int nodesBeforeThisBottomTree = topAns * (sizeOfChild + 1);
      returnAnswer = nodesBeforeThisBottomTree + childAns;
      return true;
    } else {
      // Not found, report which subtree (below our current bottom trees)
      // the key would be in.
      int subTreesFromOtherBottoms = (sizeOfChild + 1) * topAns;
      int subTreesFromThisBottom = childAns;
      returnAnswer = subTreesFromOtherBottoms + subTreesFromThisBottom;
      return false;
    }
  }
}

bool VebTree::contains(int key) const {
  
  int dummy;
  // The true indicates that this is the highest level tree, and so it
  // has an unusual number of children that must be manually checked.
  return containsHelper(key, 0, treeOrder, dummy, true);
}
