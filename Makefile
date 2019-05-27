IDIR = ./Graph
CXX = g++
CXXFLAGS = -std=c++11 -w -O2 -I $(IDIR)
UIFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

run: FORCE
	$(CXX) test/main.cpp $(CXXFLAGS) -o $@

window: FORCE
	$(CXX) ui/*.cpp $(CXXFLAGS) $(UIFLAGS) -o $@

FORCE: ;

clean:
	rm run

