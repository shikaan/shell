.POSIX:
.PHONY: all clean run

CC 			= cc
CFLAGS 	= -Wall -Wextra -Os
BUILD 	= build
LDLIBS 	= 
LDFLAGS = 

all: shell

shell: sds.o
	$(CC) $(LDFLAGS) shell.c $(BUILD)/sds.o $(LDLIBS) -o $(BUILD)/$@

sds.o: sds/sds.c sds/sds.h sds/sdsalloc.h | $(BUILD)
	$(CC) $(CFLAGS) -c sds/sds.c -o $(BUILD)/sds.o

test.o: test/test.c test/test.h | $(BUILD)
	$(CC) $(CFLAGS) -c test/test.c -o $(BUILD)/test.o
$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm -rf build

run: shell
	$(BUILD)/shell	