CLIENT		:=	client
SERVER		:=	server

# mandatory
CLIENT_SRC	:=	client.c
SERVER_SRC	:=	server.c

OBJ_DIR		:=	obj
CLIENT_OBJ	:=	$(CLIENT_SRC:%.c=$(OBJ_DIR)/%.o)
SERVER_OBJ	:=	$(SERVER_SRC:%.c=$(OBJ_DIR)/%.o)

# bonus
CLIENT_SRC_BONUS	:=	client_bonus.c
SERVER_SRC_BONUS	:=	server_bonus.c

ifeq ($(MAKECMDGOALS), bonus)
	CLIENT_OBJ = $(CLIENT_SRC_BONUS:%.c=$(OBJ_DIR)/%.o)
	SERVER_OBJ = $(SERVER_SRC_BONUS:%.c=$(OBJ_DIR)/%.o)
endif

# include
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
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(CLIENT) $(SERVER)

re: fclean all

$(info >>> default goal : $(.DEFAULT_GOAL))
$(info >>> client obj : $(CLIENT_OBJ))
$(info >>> server obj : $(SERVER_OBJ))

.PHONY: all clean fclean re bonus info
