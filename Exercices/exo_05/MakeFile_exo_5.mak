CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = exo_5
OBJ = exo_5.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

$(OBJ): exo_5.c
	$(CC) $(CFLAGS) -c exo_5.c

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)
