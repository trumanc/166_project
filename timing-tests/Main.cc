#include <iostream>
#include <stddef.h>
#include "../timing-tests/vEB-tree-wrapper.h"
#include "COTreeWrapper.h"
#include "BTreeWrapper.h"
#include "Timing.h"
#include "StdSetTree.h"
#include "HashTable.h"

bool calculate_unsigned(const char * str, size_t& value) {
  const int stack_max = 4;
  size_t stack[stack_max + 1];
  int p = -1;
  const char * s = str;
  char * end;

  // Implement little RPN calculator.
  while (*s) {
    switch (*s) {
    case '^':
      if (p < 0) {
        return false;
      }
      stack[p] = 1 << stack[p];
      s++;
      break;
    case '+':
      if (--p < 0) {
        return false;
      }
      stack[p] += stack[p + 1];
      s++;
      break;
    case '-':
      if (--p < 0) {
        return false;
      }
      stack[p] -= stack[p + 1];
      s++;
      break;
    case '*':
      if (--p < 0) {
        return false;
      }
      stack[p] *= stack[p + 1];
      s++;
      break;
    case '/':
      if (--p < 0) {
        return false;
      }
      stack[p] /= stack[p + 1];
      s++;
      break;
    default:
      if (p == stack_max) {
        return false;
      }
      stack[++p] = strtoull(s, &end, 0);
      assert(s != end);
      s = end;
    }
  }
  if (p != 0) {
    return false;
  }
  value = stack[0];
  return true;
}

enum SetType {
  VebTreeType         = 0x01,
  COTreeType          = 0x02,
  BTreeType           = 0x04,
  StdSetType          = 0x08,
  StdUnorderedSetType = 0x10,
  AllSetTypes         = 0x1F,
};

bool get_set_type(const char * set_type_str, SetType& set_type) {
  std::string set_type_string = std::string(set_type_str);
  if (set_type_string == "All") {
    set_type = AllSetTypes;
  } else if (set_type_string == "VebTree") {
    set_type = VebTreeType;
  } else if (set_type_string == "COTree") {
    set_type = COTreeType;
  } else if (set_type_string == "BTree") {
    set_type = BTreeType;
  } else if (set_type_string == "std::set") {
    set_type = StdSetType;
  } else if (set_type_string == "std::unordered_set") {
    set_type = StdUnorderedSetType;
  } else {
    return false;
  }
  return true;
}

void usage(int argc, const char * argv[]) {
  std::cout << "Usage: " << argv[0] << " <tree-size> <num-lookups> <set-type>" << std::endl;
  exit(1);
}

int main(int argc, const char * argv[]) {
  size_t TreeSize, NumLookups, NumWorkingSets;
  SetType set_type;
  if (argc < 4 ||
      !calculate_unsigned(argv[1], TreeSize) ||
      !calculate_unsigned(argv[2], NumLookups) ||
      !get_set_type(argv[3], set_type)) {
    usage(argc, argv);
  }
  NumWorkingSets = TreeSize >> 6;


  std::cout << "TreeSize:    " << TreeSize << std::endl;
  std::cout << "NumLookups:  " << NumLookups << std::endl;
  std::cout << std::endl;

//  std::cout << "Correctness Tests" << std::endl;
//  std::cout << "  VebTree:            " << (checkCorrectness<VebTreeWrapper>(TreeSize, NumLookups) ? "pass" : "fail") << std::endl;
//  std::cout << "  COTree:             " << (checkCorrectness<COTreeWrapper>(TreeSize, NumLookups) ? "pass" : "fail") << std::endl;
//  //std::cout << "  std::set:           " << (checkCorrectness<StdSetTree>(TreeSize, NumLookups) ? "pass" : "fail") << std::endl;
//  //std::cout << "  std::unordered_set: " << (checkCorrectness<HashTable>(TreeSize, NumLookups) ? "pass" : "fail") << std::endl;
//  std::cout << std::endl;

//  std::cout << "Access Elements in Sequential Order:" << std::endl;
//  std::cout << "  VebTree:            " << timeSequential<VebTreeWrapper>(TreeSize) << " ms" << std::endl;
//  std::cout << "  COTree:             " << timeSequential<COTreeWrapper>(TreeSize) << " ms" << std::endl;
//  std::cout << "  BTree:              " << timeSequential<BTreeWrapper>(TreeSize) << " ms" << std::endl;
//  std::cout << "  std::set:           " << timeSequential<StdSetTree>(TreeSize) << " ms" << std::endl;
//  std::cout << "  std::unordered_set: " << timeSequential<HashTable>(TreeSize) << " ms" << std::endl;
//  std::cout << std::endl;

//  std::cout << "Access Elements in Reverse Sequential Order:" << std::endl;
//  std::cout << "  VebTree:            " << timeReverseSequential<VebTreeWrapper>(TreeSize) << " ms" << std::endl;
//  std::cout << "  COTree:             " << timeReverseSequential<COTreeWrapper>(TreeSize) << " ms" << std::endl;
//  std::cout << "  BTree:              " << timeReverseSequential<BTreeWrapper>(TreeSize) << " ms" << std::endl;
//  std::cout << "  std::set:           " << timeReverseSequential<StdSetTree>(TreeSize) << " ms" << std::endl;
//  std::cout << "  std::unordered_set: " << timeReverseSequential<HashTable>(TreeSize) << " ms" << std::endl;
//  std::cout << std::endl;

//  std::cout << "Access Elements in Working Set Batches:" << std::endl;
//  std::cout << "  VebTree:            " << timeWorkingSets<VebTreeWrapper>(NumWorkingSets, NumWorkingSets, NumLookups) << " ms" << std::endl;
//  std::cout << "  COTree:             " << timeWorkingSets<COTreeWrapper>(NumWorkingSets, NumWorkingSets, NumLookups) << " ms" << std::endl;
//  std::cout << "  BTree:              " << timeWorkingSets<BTreeWrapper>(NumWorkingSets, NumWorkingSets, NumLookups) << " ms" << std::endl;
//  std::cout << "  std::set:           " << timeWorkingSets<StdSetTree>(NumWorkingSets, NumWorkingSets, NumLookups) << " ms" << std::endl;
//  std::cout << "  std::unordered_set: " << timeWorkingSets<HashTable>(NumWorkingSets, NumWorkingSets, NumLookups) << " ms" << std::endl;
//  std::cout << std::endl;

  auto uniform = std::uniform_int_distribution<int>(0, TreeSize-1);
  std::cout << "Access Elements Uniformly at Random:" << std::endl;
  if (set_type & VebTreeType) {
    std::cout << "  VebTree:            " << timeDistribution<VebTreeWrapper>(uniform, NumLookups) << " ms" << std::endl;
  }
  if (set_type & COTreeType) {
    std::cout << "  COTree:             " << timeDistribution<COTreeWrapper>(uniform, NumLookups) << " ms" << std::endl;
  }
  if (set_type & BTreeType) {
    std::cout << "  BTree:              " << timeDistribution<BTreeWrapper>(uniform, NumLookups) << " ms" << std::endl;
  }
  if (set_type & StdSetType) {
    std::cout << "  std::set:           " << timeDistribution<StdSetTree>(uniform, NumLookups) << " ms" << std::endl;
  }
  if (set_type & StdUnorderedSetType) {
    std::cout << "  std::unordered_set: " << timeDistribution<HashTable>(uniform, NumLookups) << " ms" << std::endl;
  }
  std::cout << std::endl;

  // Some Zipfian distributed tests
  for (double z: {0.5, 0.75, 1.0, 1.2, 1.3}) {
    auto distribution_z = zipfian(TreeSize, z);
    std::cout << "Access Elements According to a Zipf(" << z << ") Distribution:" << std::endl;
    if (set_type & VebTreeType) {
      std::cout << "  VebTree:            " << timeDistribution<VebTreeWrapper>(distribution_z, NumLookups) << " ms" << std::endl;
    }
    if (set_type & COTreeType) {
      std::cout << "  COTree:             " << timeDistribution<COTreeWrapper>(distribution_z, NumLookups) << " ms" << std::endl;
    }
    if (set_type & BTreeType) {
      std::cout << "  BTree:              " << timeDistribution<BTreeWrapper>(distribution_z, NumLookups) << " ms" << std::endl;
    }
    if (set_type & StdSetType) {
      std::cout << "  std::set:           " << timeDistribution<StdSetTree>(distribution_z, NumLookups) << " ms" << std::endl;
    }
    if (set_type & StdUnorderedSetType) {
      std::cout << "  std::unordered_set: " << timeDistribution<HashTable>(distribution_z, NumLookups) << " ms" << std::endl;
    }
    std::cout << std::endl;
  }
}
