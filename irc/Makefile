CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lws2_32
SOURCES=main.cpp IRCSocket.cpp IRCClient.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=irc.exe

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
