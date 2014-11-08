CC=gcc
CFLAGS=-Wall -std=C11
LDFLAGS=
SOURCES=src/*.c
EXECUTABLE=simbot
OBJECTS=$(SOURCES:cpp=.o)

debug : CC+= -ggdb
debug : $(SOURCES) $(EXECUTABLE)

release : $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

install-strip :
	strip $(EXECUTABLE)

clean :
	rm -fr $(EXECUTABLE) *.o
