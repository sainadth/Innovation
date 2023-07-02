CC=g++
CFLAGS=-c -Wall
LDFLAGS=

INC_DIR=inc
SRC_DIR=src
OBJ_DIR=obj

# List of header files
HEADERS=$(wildcard $(INC_DIR)/*.h)

# List of source files
SOURCES=$(wildcard $(SRC_DIR)/*.cpp)

# List of object files
OBJECTS=$(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Executable name
EXECUTABLE=rsa

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INC_DIR) $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(EXECUTABLE)