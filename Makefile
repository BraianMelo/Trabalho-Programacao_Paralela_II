# Compilador e flags
CC = gcc
CFLAGS = -I include
PTHREAD = -pthread
GPROF = -pg

# Diretórios
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# Arquivos fonte
SRC = $(wildcard $(SRC_DIR)/*.c)

# Objetos (.o)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

# Nome do executável
TARGET = Programa

all: $(TARGET)

# Linkagem final (sempre com pthread e -pg)
$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(PTHREAD) $(GPROF) -o $(TARGET)

# Compila cada .c com suporte a gprof
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(PTHREAD) $(GPROF) -c $< -o $@

# Garantir que o diretório build existe
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -f $(TARGET)
	rm -rf $(BUILD_DIR)

rebuild: clean all
