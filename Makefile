CPPFLAGS = -I./cpp-btree -I./timing-tests -std=c++11 -O3

CXX = g++

TDIR = ./timing-tests

HEADERS = cotree.h \
	  vEB-tree.h \
	  $(TDIR)/BTreeWrapper.h \
	  $(TDIR)/COTreeWrapper.h

OBJECTS = vEB-tree.o \
	  $(TDIR)/Main.o \
	  $(TDIR)/StdSetTree.o \
	  $(TDIR)/Timing.o \
	  $(TDIR)/HashTable.o \
	  $(TDIR)/vEB-tree-wrapper.o


all: run-timing-tests test tree-tester

%.o: %.cc $(HEADERS) Makefile
	$(CXX) $(CPPFLAGS) -c -o $@ $<

test: test.o vEB-tree.o
	$(CXX) $(CPPFLAGS) -o $@ $^

tree-tester: search-tree-benchmark.cc vEB-tree.o
	$(CXX) $(CPPFLAGS) $^ -o $@

run-timing-tests: $(OBJECTS)
	$(CXX) $(CPPFLAGS) -o $@ $^

clean:
	rm -rf -- *.o $(TDIR)/*.o
