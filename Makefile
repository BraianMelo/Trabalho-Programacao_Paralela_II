# Compilador e flags
CC = gcc
CFLAGS = -I include

# Diretórios
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# Lista automática de .c em src/
SRC = $(wildcard $(SRC_DIR)/*.c)

# Transforma a lista de .c em lista de .o dentro de build/
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

# Nome do executável
TARGET = Programa

all: $(TARGET)

# Geração do executável
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Regra para gerar build/*.o a partir de src/*.c
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Garante que a pasta build existe
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -f $(TARGET)
	rm -rf $(BUILD_DIR)

rebuild: clean all
