CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp util.cpp object.cpp unit.cpp creature.cpp player.cpp spell.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=game.exe

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
