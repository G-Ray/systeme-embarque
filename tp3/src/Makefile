CC=gcc
CFLAGS=-c -Wall -march=native -O3
LDFLAGS=-lrt -pthread
SOURCES=main.c
OBJECTS=$(SOURCES:.c=.o)
LIBRARIES=
EXECUTABLE=bench

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBRARIES)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *o $(EXECUTABLE) *a
