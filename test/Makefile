SENDER			:= sender
RECEIVER		:= receiver

SENDER_SRC		:= kill.c
RECEIVER_SRC	:= sigaction.c

SENDER_OBJ		:= $(SENDER_SRC:.c=.o)
RECEIVER_OBJ	:= $(RECEIVER_SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(SENDER) $(RECEIVER)

$(SENDER): $(SENDER_OBJ)
	$(CC) $(CFLAGS) $(SENDER_OBJ) -o $(SENDER)

$(RECEIVER): $(RECEIVER_OBJ)
	$(CC) $(CFLAGS) $(RECEIVER_OBJ) -o $(RECEIVER)

clean:
	$(RM) $(SENDER_OBJ) $(RECEIVER_OBJ)

fclean: clean
	$(RM) $(SENDER) $(RECEIVER)

re: fclean all

.PHONY: all clean fclean re
