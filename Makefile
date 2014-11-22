CC = clang
CFLAGS = -I/usr/include -Wall -std=c11
LDFLAGS = -L/usr/bin -lglfw -lGL
SOURCES = simbot.c
EXECUTABLE = simbot
OBJ_DIR = bin
OBJECTS = ${SOURCES:%.c=$(OBJ_DIR)/%.o}

#*******************#
#  Example targets  #
#*******************#

# // Describes how the executable is built.
#$(EXECUTABLE) :
#	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJECTS)

# // Describes how the object files are created.
#$(OBJ_DIR)/%.o : %.c
#	$(CC) $(CFLAGS) $< -o $@

#*******************#
#  ~Example targets #
#*******************#

# Default target.
all : init build strip-exec

debug : CC += -ggdb
debug : init build

build : $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE) :
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS)

# Build the src folder's sources.
$(OBJ_DIR)/%.o : src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

init :
	mkdir -p "$(OBJ_DIR)"

clean :
	rm -rf $(EXECUTABLE) $(OBJ_DIR)

strip-exec :
	strip $(EXECUTABLE)
