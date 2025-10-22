CXX=clang++
CXX=icpc
CXX=g++
CPPFLAGS=-O2 -std=c++11

all: explicit implicit sparse

explicit: explicit.o
	$(CXX) $(CPPFLAGS) -o $@ $<

implicit: implicit.o
	$(CXX) $(CPPFLAGS) -o $@ $<

sparse: sparse.o
	$(CXX) $(CPPFLAGS) -o $@ $<
