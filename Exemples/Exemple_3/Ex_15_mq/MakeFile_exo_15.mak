CC = gcc
CFLAGS = -Wall -Wextra -Werror

SENDER_OBJ = sender.o
RECEIVER_OBJ = receiver.o

all: sender receiver

sender: $(SENDER_OBJ)
	$(CC) $(CFLAGS) -o sender $(SENDER_OBJ)

receiver: $(RECEIVER_OBJ)
	$(CC) $(CFLAGS) -o receiver $(RECEIVER_OBJ)

sender.o: sender.c
	$(CC) $(CFLAGS) -c sender.c

receiver.o: receiver.c
	$(CC) $(CFLAGS) -c receiver.c

clean:
	rm -f $(SENDER_OBJ) $(RECEIVER_OBJ) sender receiver

run_sender: sender
	./sender

run_receiver: receiver
	./receiver
