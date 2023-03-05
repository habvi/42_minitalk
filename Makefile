CLIENT		:=	client
SERVER		:=	server

CLIENT_SRC	:=	client.c
SERVER_SRC	:=	server.c

OBJ_DIR		:=	obj
CLIENT_OBJ	:=	$(CLIENT_SRC:%.c=$(OBJ_DIR)/%.o)
SERVER_OBJ	:=	$(SERVER_SRC:%.c=$(OBJ_DIR)/%.o)

INCLUDE		:=	-I.
DEPS		:=	$(OBJS:.o=.d)

CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror -MMD -MP
MKDIR		:=	mkdir -p

all: $(CLIENT) $(SERVER)

bonus: all

-include $(DEPS)

$(OBJ_DIR)/%.o: %.c
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(CLIENT): $(CLIENT_OBJ)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) -o $(CLIENT)

$(SERVER): $(SERVER_OBJ)
	$(CC) $(CFLAGS) $(SERVER_OBJ) -o $(SERVER)

clean:
	$(RM) $(CLIENT_OBJ) $(SERVER_OBJ)

fclean: clean
	$(RM) $(CLIENT) $(SERVER)

re: fclean all

info:
	$(info >>> default goal : $(.DEFAULT_GOAL))

.PHONY: all clean fclean re bonus info
