# Compiler
CC = clang++

# Header files
HEADER_DIR = headers
# Compiler flags
CFLAGS = -std=c++20 -g -O0 --extra-warnings
INCLUDES = -I/usr/local/Cellar/sfml/2.6.0/include \
	   -I$(HEADER_DIR)

# Linker flags
LDFLAGS = -L/usr/local/Cellar/sfml/2.6.0/lib \
	  -lsfml-graphics -lsfml-window -lsfml-system

# Source files
SOURCE_DIR = src

# Target directory
TARGET_DIR = bin

# Executable name
EXE = $(TARGET_DIR)/sfml-app

.PHONY: all clean show

all: $(EXE)

$(EXE): tilefactory.o tileplacer.o main.o
	$(CC) -o $(EXE) $^ $(LDFLAGS)

main.o: $(SOURCE_DIR)/main.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

tilefactory.o: $(SOURCE_DIR)/tilefactory.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

tileplacer.o: $(SOURCE_DIR)/tileplacer.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
clean:
	$(RM) $(EXE) *.o

show:
	@echo "COMPILER    : $(CC)"
	@echo "BUILD FLAGS : $(CFLAGS)"
	@echo "SOURCE      : $(SOURCE_DIR)"
	@echo "HEADER DIR  : $(HEADER_DIR)"
	@echo "TARGET DIR  : $(TARGET_DIR)"
	@echo "EXECUTABLE  : $(EXE)"
