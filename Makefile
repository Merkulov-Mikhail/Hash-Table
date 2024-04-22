COMPILER=g++
HASH=hash1
OBJ_DIR=build
DEPENDENCIES=$(OBJ_DIR)/main.o $(OBJ_DIR)/list.o $(OBJ_DIR)/hashTable.o $(OBJ_DIR)/hash.o

.PHONY: all


all: mkDirs $(OBJ_DIR)/main.exe
	@echo "/--------\\"
	@echo "|  DONE  |"
	@echo "\\--------/"

run: all
	$(OBJ_DIR)/main.exe

mkDirs:
ifeq (,$(wildcard ./$(OBJ_DIR)))
	mkdir $(OBJ_DIR)
endif
ifeq (,$(wildcard ./src))
	mkdir src
endif
ifeq (,$(wildcard ./results))
	mkdir results
endif


$(OBJ_DIR)/main.exe: $(DEPENDENCIES)
	$(COMPILER) $^ -o $@

$(OBJ_DIR)/%.o: src/%.c src/list.h src/config.h
	$(COMPILER) -c $< -o $@ -D HASH=$(HASH) -D OUTPUT_FILE=\"results/$(HASH).txt\"

fullRun: $(DEPENDENCIES)
	@echo "----------GENERATING    DATA----------"
	python generate_data.py
	@echo "----------NEW DATA GENERATED----------"
	@make run HASH=hash1 OBJ_DIR=hash1
	@make run HASH=hash2 OBJ_DIR=hash2
	@make run HASH=hash3 OBJ_DIR=hash3
	@make run HASH=hash4 OBJ_DIR=hash4
	@make run HASH=hash5 OBJ_DIR=hash5
	@make run HASH=hash6 OBJ_DIR=hash6
	@make run HASH=hash7 OBJ_DIR=hash7
