CC = g++
CC_FLAGS = -Wall -Werror -std=c++11

EXECUTABLE = rshell
SOURCEDIR = src
BUILDDIR = bin

SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

all: $(OBJECTS)
		mkdir -p $(BUILDDIR)
		$(CC) $(OBJECTS) -o $(BUILDDIR)/$(EXECUTABLE)
		
rshell: $(OBJECTS)
			mkdir -p $(BUILDDIR)
			$(CC) $(OBJECTS) -o $(BUILDDIR)/$(EXECUTABLE)

%.o: %.cpp
		$(CC) -c $(CC_FLAGS) $< -o $@
		
clean:
		rm -f $(EXECUTABLE) $(OBJECTS)
		rm -rf $(BUILDDIR)