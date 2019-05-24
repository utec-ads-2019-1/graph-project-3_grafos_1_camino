IDIR = ./Graph
CXX = g++
CXXFLAGS = -std=c++11 -w -O2 -I $(IDIR)

run: FORCE
	$(CXX) test/main.cpp $(CXXFLAGS) -o $@

FORCE: ;

clean:
	rm -rf $(ODIR)
	rm run


