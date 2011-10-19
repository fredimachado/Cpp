CC=g++
CFLAGS=-g -c -Wall
LDFLAGS=-g
SOURCES=main.cpp util.cpp object.cpp unit.cpp creature.cpp player.cpp spell.cpp datastores.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=game.exe

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
