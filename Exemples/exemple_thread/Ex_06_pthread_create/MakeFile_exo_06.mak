CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = exo_6
OBJ = exo_06.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

$(OBJ): exo_06.c
	$(CC) $(CFLAGS) -c exo_06.c

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)
