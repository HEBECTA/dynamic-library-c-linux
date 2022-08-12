CC:=gcc

CPPFLAGS:=
CFLAGS:=
ASFLAGS:=
LDFLAGS:=-shared -fPIC

INSTALL_DIR:=/usr/lib

#SRC := $(wildcard *.c)
#SRC := $(SRC) ../src/print_log.c
SRC:=log.c
OBJS:=$(SRC:.c=.o)
BIN := log

.PHONY: all log clean

all: log 

install:
	install -d $(INSTALL_DIR)
	install -m 555 lib$(BIN).so $(INSTALL_DIR)


uninstall:
	$(RM) $(INSTALL_DIR)/lib$(BIN).so

log: log.c
	$(CC) -o lib$(BIN).so $(LDFLAGS) $<

clean:
	$(RM) *.so