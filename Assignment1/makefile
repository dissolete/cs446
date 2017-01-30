#------------------------------------------------------------------------------#
# DESIGN AND IMPLEMENTATION OF THIS MAKEFILE BY JAKE SHEPHERD ON 1/27/2017 FOR #
#            UNR'S CS446 - PRINCIPLES OF OPERATING SYSTEMS CLASS               #
#------------------------------------------------------------------------------#

# The target application name
TARGET = sim01

# Location of the source files
SOURCEFILES = $(wildcard src/*.cpp)

# Location of the include files
INCLUDES = $(wildcard include/*.hpp)

# Object translation
OBJECTS = $(patsubst %, bin/%, $(notdir $(SOURCEFILES:.cpp=.o)))

# Compiling shortcut
CC = g++ -std=c++11

# Compiling flags
CFLAGS = -Iinclude -c

#------------------------------------------------------------------------------#

link: precompile $(OBJECTS)
	@echo "\nLinking..."
	$(CC) $(OBJECTS) -o bin/$(TARGET)
	@echo "\nCompilation of bin/$(TARGET) has completed successfully."
	@echo "Type \"make run\" to execute application.\n"

precompile:
	@echo "Compiling as target bin/$(TARGET)\n"

#------------------------------------------------------------------------------#

bin/main.o: src/main.cpp $(INCLUDES)
	$(CC) $(CFLAGS) src/main.cpp -o bin/main.o

bin/Parser.o: src/Parser.cpp include/Parser.hpp
	$(CC) $(CFLAGS) src/Parser.cpp -o bin/Parser.o

bin/StringParser.o: src/StringParser.cpp include/StringParser.hpp
	$(CC) $(CFLAGS) src/StringParser.cpp -o bin/StringParser.o
	
#------------------------------------------------------------------------------#

.PHONY: run clean clean-o

run: bin/$(TARGET)
	bin/$(TARGET)

clean:
	rm -f $(OBJECTS) bin/$(TARGET)
	@echo "bin has been cleaned. Object files and app executable have been removed."

clean-o:
	rm -f $(OBJECTS)
	@echo "Object files have been removed. App executable remains."

list:
	@echo ""
	@echo "src: $(SOURCEFILES)\n"
	@echo "include: $(INCLUDES)\n"
	@echo "objects: $(OBJECTS)\n"

#-----------------------------<<  END MAKEFILE  >>-----------------------------#
