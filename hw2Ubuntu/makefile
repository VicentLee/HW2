.PHONY: all clean

CXX      = gcc
CFLAGS 	 = -pedantic-errors -Wall 
LIB_DIR	 = .
LDFLAGS  = -lm
TARGET   = main
INCLUDE  = -Iinc

#OBJ_FALSE		 = $(SRC:src/%.c=obj/%.o)
#OBJ_TRUE = $(SRC:src/%.c=obj/%.o)

SRC      = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

all:$(TARGET)
	@echo using user-defined makefile
$(TARGET): $(OBJ)
	$(CXX) $(CFLAGS) $(INCLUDE) $(LDFLAGS) $(OBJ) -o $(TARGET) 
	
obj/%.o: src/%.c 
	@mkdir -p $(@D)
	$(CXX) $(CFLAGS) $(INCLUDE) -o $@ -c $<

clean:
	rm -rf obj/* $(TARGET) $(TARGET).exe

new: clean $(TARGET) 
hello world
