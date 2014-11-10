CC=gcc
CFLAGS=-Wall -std=c11
LDFLAGS=-lglfw
SOURCES=src/simbot.c
EXECUTABLE=simbot
OBJECTS=$(SOURCES:.c=.o)

all : debug

debug : CC+= -ggdb
debug : $(SOURCES) $(EXECUTABLE)

release : $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o :
	$(CC) $(CFLAGS) $< -o $@

install-strip :
	strip $(EXECUTABLE)

clean :
	rm -fr $(EXECUTABLE) *.o
