CC = cc
OUT = G_HW.elf
MAKE = Task2

CODE = code
BIN = bin
CLEAN_COMMAND = rm -rf $(BIN)/*.o *.o

LIBS = 

BIN_FILES = $(BIN)/main.o

all: $(MAKE)

rebuild: clean all

$(MAKE): $(BIN_FILES)
	$(CC) $(BIN_FILES) $(LIBS) -o "$(OUT)"
	
$(BIN)/main.o:
	$(CC) -c "$(CODE)/main.c" -o "$(BIN)/main.o"
	
	
	
main.o:
	rm -rf "$(BIN)/main.o"
	$(CC) -c "$(CODE)/main.c" -o "$(BIN)/main.o"
	$(CC) $(BIN_FILES) $(LIBS) -o "$(OUT)"
	
	
clean:
	$(CLEAN_COMMAND)







