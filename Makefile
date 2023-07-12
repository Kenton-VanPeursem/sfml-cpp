# Compiler
CC = clang++

# Compiler flags
CFLAGS = -I/usr/local/Cellar/sfml/2.6.0/include

# Linker flags
LDFLAGS = -L/usr/local/Cellar/sfml/2.6.0/lib -lsfml-graphics -lsfml-window -lsfml-system


# Source files
SOURCE_DIR = src

# Target directory
TARGET_DIR = bin

# Executable name
EXE = $(TARGET_DIR)/sfml-app


.PHONY: all clean
all: $(EXE)

$(EXE): main.o
	$(CC) -o $(EXE) main.o $(LDFLAGS)


main.o: $(SOURCE_DIR)/main.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -f $(EXE) *.o
