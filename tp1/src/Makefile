CC=gcc
CFLAGS=-c -Wall -march=native -O3
LDFLAGS=
SOURCES=main.c colimacon.c tests.c
OBJECTS=$(SOURCES:.c=.o)
LIBRARIES=libcolimacon.a
EXECUTABLE=colimacon

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	ar rcs libcolimacon.a colimacon.o
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBRARIES)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *o $(EXECUTABLE) *a
