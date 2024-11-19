CXX = g++ -std=c++20 
EXEC = run
CXXFLAGS = -Wall -g -O -MMD
SOURCES = main.cc board.cc asset.cc criterion.cc goal.cc player.cc tile.cc
OBJECTS = $(SOURCES:.cc=.o)
DEPENDS = $(SOURCES:.cc=.d)

# Target to build the executable
$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXEC) $(CXXFLAGS) $(LDFLAGS)

# Compile each .cc file into a .o file
%.o: %.cc 
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Include the dependency files for make to track header dependencies
-include $(DEPENDS)

# Clean up build files
.PHONY: clean
clean:
	rm -f $(OBJECTS) $(DEPENDS) $(EXEC)