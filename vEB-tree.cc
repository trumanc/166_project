#include "vEB-tree.h"
#include "math.h"

#include <iostream>
using namespace std;
VebTree::VebTree(std::vector<int> keys){
  tree = vector<int>(keys.size()); // This will order the vals into a tree
  if (keys.size() < 2) {
    cout << "Cannot create a vEB tree of size < 2. Exiting..." << endl;
    exit(-1);
  }
  int height = (int)log2((double)keys.size()) + 1;
  cout << "H: " << height << endl;
  int pwrOfTwo = 1;
  while(pwrOfTwo < height) {
    pwrOfTwo *= 2;
  }
  pwrOfTwo /= 2;

  cout << "POWER: " << pwrOfTwo << endl;
  int sizeB = (1 << pwrOfTwo) -1;
  int nSeg = (keys.size() - 1) / sizeB;
  int nTop = keys.size() - (nSeg * sizeB);

  cout << "N: " << keys.size() << ", nTop: " << nTop <<
        ", sizeB: " << sizeB << ", nSeg: " << nSeg << endl;

  vector<int> topElems;
  int currIndex = nTop; // Reserve the first nTop indices for our top tree
  for (int i = 0; i < nSeg; i++) {
    recursivelyPlace(keys, i * (sizeB + 1), tree, currIndex, sizeB);
    currIndex += sizeB;
    if (currIndex < keys.size()) {
      topElems.push_back(keys[((i+1) * (sizeB + 1))-1]);
     // tree[i] = keys[((i+1) * (sizeB + 1))-1];
    }
  }
  recursivelyPlace(topElems, 0, tree, 0, nTop);
  cout << "The elems in the top tree are: " << endl;
  int counter = 0;
  for (int x : tree) {
    counter++;
    cout << counter << ":  " << x << endl;
  }
}

void inOrderPrint(vector<int>& tree, int currIndex, int size) {
  //if (currIndex < 0 || currIndex > tree.size()) return;
  if (size == 1) {
    cout << tree[currIndex] << endl;
    return;
  }
  int subTreeSize = sqrt(size + 1) - 1;
  int numChildren = (size / subTreeSize ) -1; 
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
  cout << "inputStart: " << inputMinIndex << ", TreeStart: " <<  treeMinIndex
       << ", length: " << size << endl;  
  if (!isPerfectSubTreeSize(size)) {
    cout << "Attempted to recursively place a tree of size " << size << endl;
    exit(1);
  }
  if (size == 1) {// Base case! size one is easy
    tree[treeMinIndex] = sortedInput[inputMinIndex];
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
      topElems.push_back(sortedInput[inputMinIndex +
                                     ((child+1) * (subTreeSize + 1))-1]);
    }
  }

  // All the bottom trees have been placed. Now add the topElems into the space
  // we reserved earlier
  recursivelyPlace(topElems, 0, tree, treeMinIndex, subTreeSize);
}
  


int VebTree::getPredecessor(int key) {
  return key;
}
