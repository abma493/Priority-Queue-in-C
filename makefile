SRC = *.c
OBJ = $(SRC: .c = .o) #objs are both .c and .o
BIN = Executable
CFLAGS = -Wall -O2
# -Wall recommends compiler warnings
# -O2   recommends optimizations

$(BIN): $(OBJ)
	gcc $^ $(CFLAGS) -o $@
%.o: %.c
	gcc -c $^ $(CFLAGS) -o $@
clean:
	rm -rf *.o $(BIN)

# -r --recursive 
# -f --force (ignore nonexistent files and args, never prompt)
	