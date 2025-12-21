# Compiler
CXX = g++
# Compiler flags
CXXFLAGS = -std=c++17 -Wall

# Directories
SRCDIR = .
BUILDDIR = build

# Find all .cpp files in the source directory
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

# Separate sources with main() from other sources
MAIN_SOURCES = $(shell grep -l "main" $(SOURCES))
OTHER_SOURCES = $(filter-out $(MAIN_SOURCES), $(SOURCES))

# Executables are based on files with a main() function
EXECUTABLES = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%,$(MAIN_SOURCES))

# Object files for non-main sources
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(OTHER_SOURCES))

# Default target: build all executables
all: $(EXECUTABLES)

# Rule to build executables
# It depends on the corresponding main source file and all non-main object files
$(BUILDDIR)/%: $(SRCDIR)/%.cpp $(OBJECTS)
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -o $@ $< $(OBJECTS)

# Rule to build object files from non-main sources
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Phony target to run executables
.PHONY: run
run-%:
	@$(MAKE) --no-print-directory $(BUILDDIR)/$*
	@./$(BUILDDIR)/$*

# Phony target to clean the build directory
.PHONY: clean
clean:
	rm -rf $(BUILDDIR)

# List available executables
list:
	@echo "Available executables to run:"
	@$(foreach exec,$(EXECUTABLES),echo "  - make run-$(notdir $(exec))";)