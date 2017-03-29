#Declaration of variables

CC = g++
CC_FLAGS = -Wall -Werror -pedantic -std=c++14 -DGLEW_STATIC
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

#File names
EXEC = run
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

#Main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) -o $(EXEC)

# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)
