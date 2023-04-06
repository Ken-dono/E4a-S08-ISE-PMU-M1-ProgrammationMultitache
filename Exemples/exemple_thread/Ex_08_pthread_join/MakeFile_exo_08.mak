CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = exo_8
OBJ = exo_08.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

$(OBJ): exo_08.c
	$(CC) $(CFLAGS) -c exo_08.c

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)
