CXXFLAGS += -Wall -Wextra -pedantic-errors

LDLIBS := $(shell pkg-config sfml-all --libs)

SOURCES := $(wildcard *.cpp)
PROGRAMS := $(patsubst %.cpp,%,$(SOURCES))

all: $(PROGRAMS)

clean:
	$(RM)	$(PROGRAMS)
