
## Files and directories
SRCDIR := src
INCDIR := inc
BUILDDIR := obj
TARGET := pacman
TARGETDIR := bin
RESDIR := res
SRCEXT := cpp
OBJEXT := o

## Flags to linker & compiler
CC = g++
CC_FLAGS = -Wall -Werror -pedantic -std=c++14 -DGLEW_STATIC -O3
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
INC := -I$(INCDIR)



print-%  : ; @echo $* = $($*)


### FUNSTUFF
SOURCES := $(shell find $(SRCDIR) -type f -name '*.$(SRCEXT)')
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))


#Defauilt Make
all: resources $(TARGET)


resources : directories
	@cp -r $(RESDIR) $(TARGETDIR)/

#Make the Directories
directories:
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(BUILDDIR)


#Link
$(TARGET): $(OBJECTS)
	$(CC) $(LIBS) -o $(TARGETDIR)/$(TARGET) $^

#Compile
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) $(INC) -c -o $@ $<



#Clean only Objecst
clean: 
	rm -f $(OBJECTS)
	rm -f $(TARGETDIR)/$(TARGET)

