CC=gcc
CFLAGS=-c -Wall -march=native -O3
LDFLAGS=
SOURCES=main.c doubly_linked_list.c hash_table.c
OBJECTS=$(SOURCES:.c=.o)
LIBRARIES=libDoublyLinkedList.a libHashTable.a
EXECUTABLE=linked_list

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	ar rcs libDoublyLinkedList.a doubly_linked_list.o
	ar rcs libHashTable.a hash_table.o
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBRARIES)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *o $(EXECUTABLE) *.a
