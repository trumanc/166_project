CPPFLAGS = -I./cpp-btree -std=c++11 -O3

CXXFLAGS = -std=c++11 -I./timing-tests -Wall -Werror -O3 
CXX = g++
TDIR = ./timing-tests
OBJECTS = $(TDIR)/Main.o $(TDIR)/StdSetTree.o $(TDIR)/Timing.o vEB-tree.o $(TDIR)/HashTable.o

run-timing-tests: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

program: search-tree-benchmark.cc vEB-tree.o
	g++ search-tree-benchmark.cc vEB-tree.o -o tree-tester $(CPPFLAGS)

vEB-tree.o: vEB-tree.h vEB-tree.cc
	g++ vEB-tree.cc -c $(CPPFLAGS)

$(TDIR)/Main.o: $(TDIR)/Main.cc $(TDIR)/Timing.h $(TDIR)/StdSetTree.h vEB-tree.h

$(TDIR)/StdSetTree.o: $(TDIR)/StdSetTree.cc $(TDIR)/StdSetTree.h

$(TDIR)/HashTable.o: $(TDIR)/HashTable.cc $(TDIR)/HashTable.h

$(TDIR)/Timing.o: $(TDIR)/Timing.cc $(TDIR)/Timing.h

clean :
	rm -f $(TDIR)/Main.o $(TDIR)/StdSetTree.o $(TDIR)/Timing.o vEB-tree.o $(TDIR)/HashTable.o tree-tester run-timing-tests 
