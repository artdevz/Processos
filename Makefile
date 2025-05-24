# Compiladores
CC = gcc
CXX = g++

# Diretórios
OBJ_DIR = obj
BIN_DIR = bin
Q1_INC = quest01/include
Q2_INC = quest02/include
Q3_INC = quest03/include

# Arquivos fonte
Q1_SRC = quest01/src/main.cpp quest01/src/Scheduler.cpp
Q2_SRC = quest02/src/main.cpp
Q3_SRC = quest03/src/main.cpp

# Objetos com nomes distintos
Q1_OBJ = $(OBJ_DIR)/quest01_main.o $(OBJ_DIR)/Scheduler.o
Q2_OBJ = $(OBJ_DIR)/quest02.o
Q3_OBJ = $(OBJ_DIR)/quest03.o

# Executáveis
Q1_EXE = $(BIN_DIR)/quest01
Q2_EXE = $(BIN_DIR)/quest02
Q3_EXE = $(BIN_DIR)/quest03

# Flags
CFLAGS = -Wall -Wextra -pthread
CXXFLAGS = -Wall -Wextra -std=c++17 -I$(Q1_INC) -I$(Q3_INC)

.PHONY: all clean

all: $(Q1_EXE) $(Q2_EXE) $(Q3_EXE)

# Compila Questão 1 (C++)
$(Q1_EXE): $(Q1_OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(Q1_OBJ) -o $@

$(OBJ_DIR)/quest01_main.o: quest01/src/main.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/Scheduler.o: quest01/src/Scheduler.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compila Questão 2 (C++)
$(Q2_EXE): $(Q2_OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(Q2_OBJ) -o $@

$(Q2_OBJ): $(Q2_SRC)
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compila Questão 3 (C++)
$(Q3_EXE): $(Q3_OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(Q3_OBJ) -o $@

$(Q3_OBJ): $(Q3_SRC)
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpa todos os binários e objetos
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
