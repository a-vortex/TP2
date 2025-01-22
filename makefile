# Compilador e flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -g 

# Diretórios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include

# Arquivo executável
TARGET = $(BIN_DIR)/tp2.out

# Arquivos fonte e objetos
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

# Regras de compilação
all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Limpeza
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
