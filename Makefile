CC = cc

CODE = code
BIN = bin

CLEAN_COMMAND = rm -rf $(BIN)/*.o *.o

LIBS = 

SORTS = "$(BIN)/ShakeSort.o" "$(BIN)/IntroSort.o"

all: timing check

array_creator:
	rm -rf "$(BIN)/ArrayFileCreator.o"
	$(CC) -c "$(CODE)/ArrayFileCreator.c" -o "$(BIN)/ArrayFileCreator.o"
	$(CC) "$(BIN)/ArrayFileCreator.o" -o "ArrCreator.elf"
	
timing: $(SORTS) "$(BIN)/main_timing.o"
	$(CC) $(SORTS) "$(BIN)/main_timing.o" -o "Timing.elf"
	
check: $(SORTS) "$(BIN)/main_check.o"
	$(CC) $(SORTS) "$(BIN)/main_check.o" -o "Check.elf"
	
test: $(SORTS) "$(BIN)/main_test.o"
	$(CC) $(SORTS) "$(BIN)/main_test.o" -o "Test.elf"
	

rebuild: clean all
	
"$(BIN)/main_timing.o":
	$(CC) -c "$(CODE)/main_timing.c" -o "$(BIN)/main_timing.o"
	
"$(BIN)/main_check.o":
	$(CC) -c "$(CODE)/main_check.c" -o "$(BIN)/main_check.o"
	
"$(BIN)/main_test.o":
	$(CC) -c "$(CODE)/main_test.c" -o "$(BIN)/main_test.o"
	
	
	
"$(BIN)/IntroSort.o":
	$(CC) -c "$(CODE)/IntroSort.c" -o "$(BIN)/IntroSort.o"
	
"$(BIN)/ShakeSort.o":
	$(CC) -c "$(CODE)/ShakeSort.c" -o "$(BIN)/ShakeSort.o"
	
IntroSort.o:
	rm -rf "$(BIN)/IntroSort.o"
	$(CC) -c "$(CODE)/IntroSort.c" -o "$(BIN)/IntroSort.o"
	
ShakeSort.o:
	rm -rf "$(BIN)/ShakeSort.o"
	$(CC) -c "$(CODE)/ShakeSort.c" -o "$(BIN)/ShakeSort.o"
	
	
clean:
	$(CLEAN_COMMAND)







