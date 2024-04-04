CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SRCDIR=./
BINDIR=bin
SOURCES=$(shell find $(SRCDIR) -name '*.cpp')
OBJECTS=$(SOURCES:$(SRCDIR)/%.cpp=$(BINDIR)/%.o)
EXECUTABLE=./bin/main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(BINDIR) $(EXECUTABLE)