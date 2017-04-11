
## Files and directories
SRCDIR := src
INCDIR := inc
BUILDDIR := obj
TARGET := pacman
TARGETDIR := bin
SRCEXT := cpp
OBJEXT := o

## Flags to linker & compiler
CC = g++
CC_FLAGS = -Wall -Werror -pedantic -std=c++14 -DGLEW_STATIC
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
INC := -I$(INCDIR)



print-%  : ; @echo $* = $($*)


### FUNSTUFF
SOURCES := $(shell find $(SRCDIR) -type f -name '*.$(SRCEXT)')
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))


#Defauilt Make
all: $(TARGET)

#Make the Directories
directories:
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(BUILDDIR)


#Link
$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGETDIR)/$(TARGET) $^ $(LIB)

#Compile
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) $(INC) -c -o $@ $<



#Clean only Objecst
clean: 
	rm -f $(OBJECTS)
	rm -f $(TARGETDIR)/$(TARGET)

