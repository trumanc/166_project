CPPFLAGS=-g -I./cpp-btree -std=c++11 -lm

program: search-tree-benchmark.cc vEB-tree.o
	g++ search-tree-benchmark.cc vEB-tree.o -o tree-tester $(CPPFLAGS)

vEB-tree.o: vEB-tree.h vEB-tree.cc
	g++ vEB-tree.cc -c $(CPPFLAGS)

clean :
	rm *.0
