CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = exo_2
OBJ = exo_02.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

$(OBJ): exo_02.c
	$(CC) $(CFLAGS) -c exo_02.c

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)
