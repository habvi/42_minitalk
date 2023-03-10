CLIENT				:=	client
SERVER				:=	server

# mandatory
CLIENT_SRC			:=	client.c error.c
SERVER_SRC			:=	server.c error.c

OBJ_DIR				:=	obj
CLIENT_OBJ			:=	$(CLIENT_SRC:%.c=$(OBJ_DIR)/%.o)
SERVER_OBJ			:=	$(SERVER_SRC:%.c=$(OBJ_DIR)/%.o)

# bonus
CLIENT_SRC_BONUS	:=	client_bonus.c
SERVER_SRC_BONUS	:=	server_bonus.c

SRCS				:=	$(CLIENT_SRC) $(SERVER_SRC) $(CLIENT_SRC_BONUS) $(SERVER_SRC_BONUS)

# ok..?
ifeq ($(MAKECMDGOALS), bonus)
	CLIENT_OBJ = $(CLIENT_SRC_BONUS:%.c=$(OBJ_DIR)/%.o)
	SERVER_OBJ = $(SERVER_SRC_BONUS:%.c=$(OBJ_DIR)/%.o)
endif

# libft
LIBFT_DIR			:=	libft
LIBFT				:=	$(LIBFT_DIR)/libft.a

# include
INCLUDE_DIR			:=	include
INCLUDES			:=	-I. -I$(LIBFT_DIR)/$(INCLUDE_DIR)/
DEPS				:=	$(OBJS:.o=.d)

CC					:=	cc
CFLAGS				:=	-Wall -Wextra -Werror -MMD -MP
MKDIR				:=	mkdir -p

all: $(CLIENT) $(SERVER)

bonus: all

-include $(DEPS)

$(LIBFT): FORCE
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: %.c
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(CLIENT): $(CLIENT_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(CLIENT_OBJ) $(LIBFT)

$(SERVER): $(SERVER_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(SERVER_OBJ) $(LIBFT)

clean:
	$(RM) -r $(OBJ_DIR) $(LIBFT_DIR)/$(OBJ_DIR)

fclean: clean
	$(RM) $(CLIENT) $(SERVER) $(LIBFT)

re: fclean all

norm:
	norminette $(SRCS)

norm_with_libft:
	norminette $(SRCS) $(LIBFT_DIR)

FORCE:

$(info >>> default goal : $(.DEFAULT_GOAL))
$(info >>> client obj : $(CLIENT_OBJ))
$(info >>> server obj : $(SERVER_OBJ))

.PHONY: all clean fclean re bonus info FORCE norm norm_with_libft
