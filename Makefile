# Compilador e flags
CC = gcc
CFLAGS = -I include
PTHREAD = -pthread

# Diretórios
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# Arquivos fonte
SRC = $(wildcard $(SRC_DIR)/*.c)

# Arquivos objeto
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

# Filtra apenas o arquivo paralelo e seu objeto
PAR_SRC = $(SRC_DIR)/Jogo_Vida_Conway_Paralelo.c
PAR_OBJ = $(BUILD_DIR)/Jogo_Vida_Conway_Paralelo.o

# Executáveis
SEQ_TARGET = Programa
PAR_TARGET = ProgramaParalelo

all: $(SEQ_TARGET) $(PAR_TARGET)

# Liga executável sequencial
$(SEQ_TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(SEQ_TARGET)

# Liga executável paralelo (precisa de pthread)
$(PAR_TARGET): $(OBJ)
	$(CC) $(OBJ) $(PTHREAD) -o $(PAR_TARGET)

# Compila objetos normais
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Pasta build
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -f $(SEQ_TARGET) $(PAR_TARGET)
	rm -rf $(BUILD_DIR)

rebuild: clean all
