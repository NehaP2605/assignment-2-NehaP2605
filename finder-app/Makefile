#compiler selection
CC := $(CROSS_COMPILE)g++
CFLAGS ?= -std=c++17 -Wall -g
LDFLAGS ?=

$(info Using compiler : $(CC))

#source and object files
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
TARGET = writer

#default target
all: $(TARGET)

#linking executables
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJ)

#compile cpp -> o
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

#clean target
clean:
	rm -f $(TARGET) $(OBJ)
