.POSIX:
.PHONY: all clean test run

CC 			= cc
CFLAGS 	= -Wall -Wextra -Os
BUILD 	= build
LDLIBS 	= 
LDFLAGS = 

all: shell

shell: sds.o $(BUILD)/string.o $(BUILD)/builtin.o $(BUILD)/process.o
	$(CC) $(LDFLAGS) shell.c $(BUILD)/sds.o $(BUILD)/string.o $(BUILD)/builtin.o $(BUILD)/process.o $(LDLIBS) -o $(BUILD)/$@

# Dependencies
sds.o: sds/sds.c sds/sds.h sds/sdsalloc.h | $(BUILD)
	$(CC) $(CFLAGS) -c sds/sds.c -o $(BUILD)/sds.o

# Test
builtin.test: test.o sds.o $(BUILD)/builtin.o
	$(CC) $(LDFLAGS) test/$@.c $(BUILD)/test.o $(BUILD)/sds.o $(BUILD)/builtin.o $(LDLIBS) -o $(BUILD)/$@

string.test: test.o sds.o $(BUILD)/string.o
	$(CC) $(LDFLAGS) test/$@.c $(BUILD)/test.o $(BUILD)/sds.o $(BUILD)/string.o $(LDLIBS) -o $(BUILD)/$@

test.o: test/test.c test/test.h | $(BUILD)
	$(CC) $(CFLAGS) -c test/test.c -o $(BUILD)/test.o

# Utilities
$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/%.o: %.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

# Phony targets
test: builtin.test string.test
	$(BUILD)/builtin.test
	$(BUILD)/string.test

clean:
	rm -rf build

run: shell
	$(BUILD)/shell	