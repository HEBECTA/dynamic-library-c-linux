CC:=gcc
CPPFLAGS:=-I../lib/
CFLAGS:=
ASFLAGS:=
LDFLAGS:=-L../lib -llog -lsqlite3


SRC := $(wildcard *.c)
OBJS:=$(SRC:.c=.o)

BINS:= write_log write_log2 print_log

.PHONY: all clean

all: $(BINS)

write_log: write_log.o
	$(CC) -o ../$@  $< $(LDFLAGS)

write_log2: write_log2.o
	$(CC) -o ../$@  $< $(LDFLAGS)

print_log: print_log.o
	$(CC) -o ../$@  $< $(LDFLAGS)

%.o:%.c
	$(CC) -o $@ -c $^ $(CPPFLAGS)

clean:
	$(RM) $(OBJS) ../write_log ../write_log2  ../print_log
