CPPFLAGS = -I./cpp-btree -I./timing-tests -std=c++11 -O3

CXX = g++
HEADERS = cotree.h vEB-tree.h
TDIR = ./timing-tests
OBJECTS = $(TDIR)/Main.o $(TDIR)/StdSetTree.o $(TDIR)/Timing.o vEB-tree.o $(TDIR)/HashTable.o $(TDIR)/vEB-tree-wrapper.o


all: run-timing-tests test tree-tester

run-timing-tests: $(OBJECTS)
	$(CXX) $(CPPFLAGS) -o $@ $^

%.o: %.cc $(HEADERS)
	$(CXX) $(CPPFLAGS) -c -o $@ $<

test: test.o vEB-tree.o
	$(CXX) $(CPPFLAGS) -o $@ $^

tree-tester: search-tree-benchmark.cc vEB-tree.o
	g++ search-tree-benchmark.cc vEB-tree.o -o $@ $(CPPFLAGS)

vEB-tree.o: vEB-tree.h vEB-tree.cc
	g++ vEB-tree.cc -c $(CPPFLAGS)

clean:
	rm -f -- *.o 
	rm -rf -- $(TDIR)/*.o
