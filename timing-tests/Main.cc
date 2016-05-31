#include <iostream>
#include <stddef.h>
#include "../timing-tests/vEB-tree-wrapper.h"
#include "Timing.h"
#include "StdSetTree.h"
#include "HashTable.h"

/* Constant controlling how many elements we'll put into each BST when
 * doing time trials.
 */
const size_t kTreeSize = 1 << 20;

/* Constant controlling the number of lookups to perform on those trees
 * when doing time trials.
 */
const size_t kNumLookups = 1 << 18;

/* For the "working set" test case, the number of working sets. */
const size_t kNumWorkingSets = kTreeSize >> 6;

int main() {
  std::cout << "Correctness Tests" << std::endl;
  std::cout << "  VebTreeWrapper:           " << (checkCorrectness<VebTreeWrapper>(kTreeSize, kNumLookups) ? "pass" : "fail") << std::endl;
  std::cout << "  std::set:           " << (checkCorrectness<StdSetTree>(kTreeSize, kNumLookups) ? "pass" : "fail") << std::endl;
  std::cout << "  std::unordered_set: " << (checkCorrectness<HashTable>(kTreeSize, kNumLookups) ? "pass" : "fail") << std::endl;
  std::cout << std::endl;

  std::cout << "Access Elements in Sequential Order:" << std::endl;
  std::cout << "  VebTreeWrapper:           " << timeSequential<VebTreeWrapper>(kTreeSize) << " ms" << std::endl;
  std::cout << "  std::set:           " << timeSequential<StdSetTree>(kTreeSize) << " ms" << std::endl;
  std::cout << "  std::unordered_set: " << timeSequential<HashTable>(kTreeSize) << " ms" << std::endl;
  std::cout << std::endl;

  std::cout << "Access Elements in Reverse Sequential Order:" << std::endl;
  std::cout << "  VebTreeWrapper:           " << timeReverseSequential<VebTreeWrapper>(kTreeSize) << " ms" << std::endl;
  std::cout << "  std::set:           " << timeReverseSequential<StdSetTree>(kTreeSize) << " ms" << std::endl;
  std::cout << "  std::unordered_set: " << timeReverseSequential<HashTable>(kTreeSize) << " ms" << std::endl;
  std::cout << std::endl;

  std::cout << "Access Elements in Working Set Batches:" << std::endl;
  std::cout << "  VebTreeWrapper:           " << timeWorkingSets<VebTreeWrapper>(kNumWorkingSets, kNumWorkingSets, kNumLookups) << " ms" << std::endl;
  std::cout << "  std::set:           " << timeWorkingSets<StdSetTree>(kNumWorkingSets, kNumWorkingSets, kNumLookups) << " ms" << std::endl;
  std::cout << "  std::unordered_set: " << timeWorkingSets<HashTable>(kNumWorkingSets, kNumWorkingSets, kNumLookups) << " ms" << std::endl;
  std::cout << std::endl;

  auto uniform = std::uniform_int_distribution<int>(0, kTreeSize-1);
  std::cout << "Access Elements Uniformly at Random:" << std::endl;
  std::cout << "  VebTreeWrapper:           " << timeDistribution<VebTreeWrapper>(uniform, kNumLookups) << " ms" << std::endl;
  std::cout << "  std::set:           " << timeDistribution<StdSetTree>(uniform, kNumLookups) << " ms" << std::endl;
  std::cout << "  std::unordered_set: " << timeDistribution<HashTable>(uniform, kNumLookups) << " ms" << std::endl;
  std::cout << std::endl;

  // Some Zipfian distributed tests
  for (double z: {0.5, 0.75, 1.0, 1.2, 1.3}) {
    auto distribution_z = zipfian(kTreeSize, z);
    std::cout << "Access Elements According to a Zipf(" << z << ") Distribution:" << std::endl;
    std::cout << "  VebTreeWrapper:           " << timeDistribution<VebTreeWrapper>(distribution_z, kNumLookups) << " ms" << std::endl;
    std::cout << "  std::set:           " << timeDistribution<StdSetTree>(distribution_z, kNumLookups) << " ms" << std::endl;
    std::cout << "  std::unordered_set: " << timeDistribution<HashTable>(distribution_z, kNumLookups) << " ms" << std::endl;
    std::cout << std::endl;
  }
}
