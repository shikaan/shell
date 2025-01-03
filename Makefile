.POSIX:
.PHONY: all clean test run

CC 			= cc
CFLAGS 	= -Wall -Wextra -Os
BUILD 	= build
LDLIBS 	= 
LDFLAGS = 

all: shell

shell: sds.o builtin.o
	$(CC) $(LDFLAGS) shell.c $(BUILD)/sds.o $(BUILD)/builtin.o $(LDLIBS) -o $(BUILD)/$@

# Modules
builtin.o: builtin.c builtin.h | $(BUILD)
	$(CC) $(CFLAGS) -c builtin.c -o $(BUILD)/builtin.o

# Dependencies
sds.o: sds/sds.c sds/sds.h sds/sdsalloc.h | $(BUILD)
	$(CC) $(CFLAGS) -c sds/sds.c -o $(BUILD)/sds.o

# Test
builtin.test: test.o sds.o builtin.o
	$(CC) $(LDFLAGS) test/builtin.test.c $(BUILD)/test.o $(BUILD)/sds.o $(BUILD)/builtin.o $(LDLIBS) -o $(BUILD)/$@

test.o: test/test.c test/test.h | $(BUILD)
	$(CC) $(CFLAGS) -c test/test.c -o $(BUILD)/test.o

# Utilities
$(BUILD):
	mkdir -p $(BUILD)

# Phony targets
test: builtin.test
	$(BUILD)/builtin.test

clean:
	rm -rf build

run: shell
	$(BUILD)/shell	