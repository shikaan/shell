.POSIX:
.PHONY: all clean

CC 			= cc
CFLAGS 	= -Wall -Wextra -Os
BUILD 	= build
LDLIBS 	= 
LDFLAGS = 

all: shell

shell: sds.o
	$(CC) $(LDFLAGS) shell.c $(BUILD)/sds.o $(LDLIBS) -o $(BUILD)/$@

sds.o: sds/sds.c sds/sds.h sds/sdsalloc.h | $(BUILD)
	$(CC) -c $(CFLAGS) sds/sds.c -o $(BUILD)/sds.o

$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm -rf build