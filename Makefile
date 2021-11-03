CC = cc
OUT = G_HW.elf
MAKE = Task2

CODE = code
BIN = bin
CLEAN_COMMAND = rm -rf $(BIN)/*.o *.o

LIBS = 

BIN_FILES = "$(BIN)/main.o" "$(BIN)/ShakeSort.o"

all: $(MAKE)

array_creator:
	rm -rf "$(BIN)/ArrayFileCreator.o"
	$(CC) -c "$(CODE)/ArrayFileCreator.c" -o "$(BIN)/ArrayFileCreator.o"
	$(CC) "$(BIN)/ArrayFileCreator.o" -o "ArrCreator.elf"

rebuild: clean all

$(MAKE): $(BIN_FILES)
	$(CC) $(BIN_FILES) $(LIBS) -o "$(OUT)"
	
"$(BIN)/main.o":
	$(CC) -c "$(CODE)/main.c" -o "$(BIN)/main.o"
	
"$(BIN)/ShakeSort.o":
	$(CC) -c "$(CODE)/ShakeSort.c" -o "$(BIN)/ShakeSort.o"
	
	
main.o:
	rm -rf "$(BIN)/main.o"
	$(CC) -c "$(CODE)/main.c" -o "$(BIN)/main.o"
	$(CC) $(BIN_FILES) $(LIBS) -o "$(OUT)"
	
ShakeSort.o:
	rm -rf "$(BIN)/ShakeSort.o"
	$(CC) -c "$(CODE)/ShakeSort.c" -o "$(BIN)/ShakeSort.o"
	$(CC) $(BIN_FILES) $(LIBS) -o "$(OUT)"
	
	
clean:
	$(CLEAN_COMMAND)







