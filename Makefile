CXX = g++
CXXFLAGS = -std=c++11 -w -O2
UIFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

run: FORCE
	$(CXX) test/main.cpp $(CXXFLAGS) -o $@

window: FORCE
	$(CXX) ui/src/*.cpp $(CXXFLAGS) $(UIFLAGS) -o $@

FORCE: ;

clean:
	rm run window

