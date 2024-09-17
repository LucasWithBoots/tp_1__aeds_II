# Nome do projeto
PROJ_NAME=labirinto

# Diretórios
SRC_DIR=./source
OBJ_DIR=./objects

# Arquivos fonte .c
C_SOURCE=$(wildcard $(SRC_DIR)/*.c)

# Arquivos objeto
OBJ=$(subst $(SRC_DIR),$(OBJ_DIR),$(C_SOURCE:.c=.o))

# Compilador
CC=gcc

# Flags (opções) para o compilador
CC_FLAGS=-c         \
         -W         \
         -Wall      \
         -pedantic  \
         -std=c99

# Comando utilizado no target clean
RM = rm -rf

#########################
# Compilação e linkagem #
#########################
all: objFolder $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	@ echo 'Construindo o binário usando o linker GCC: $@'
	$(CC) $^ -o $@
	@ echo 'Binário pronto!: $@'
	@ echo ' '

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@ echo 'Construindo target usando o compilador GCC: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

objFolder:
	@ mkdir -p $(OBJ_DIR)

clean:
	@ $(RM) $(OBJ_DIR)/*.o $(PROJ_NAME) *~
	@ rmdir $(OBJ_DIR)

.PHONY: all clean
