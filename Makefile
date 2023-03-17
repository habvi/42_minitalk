#--------------------------------------------
# target
#--------------------------------------------
CLIENT				:=	client
SERVER				:=	server

#--------------------------------------------
# common
#--------------------------------------------
COMMON_SRC			:=	args.c \
						error.c \
						put.c \
						recieve.c \
						signal.c

#--------------------------------------------
# dir
#--------------------------------------------
SRC_DIR				:=	src
OBJ_DIR				:=	obj
CLIENT_DIR			:=	client
SERVER_DIR			:=	server

#--------------------------------------------
# obj dir
#--------------------------------------------
CLIENT_OBJ_DIR		:=	$(OBJ_DIR)/$(CLIENT_DIR)
SERVER_OBJ_DIR		:=	$(OBJ_DIR)/$(SERVER_DIR)

#--------------------------------------------
# mandatory
#--------------------------------------------
CLIENT_SRC_DIR		:=	$(SRC_DIR)/$(CLIENT_DIR)
SERVER_SRC_DIR		:=	$(SRC_DIR)/$(SERVER_DIR)

CLIENT_SRC			:=	$(COMMON_SRC) \
						client.c  \
						send.c
SERVER_SRC			:=	$(COMMON_SRC) \
						server.c

CLIENT_OBJS			:=	$(CLIENT_SRC:%.c=$(CLIENT_OBJ_DIR)/%.o)
SERVER_OBJS			:=	$(SERVER_SRC:%.c=$(SERVER_OBJ_DIR)/%.o)

#--------------------------------------------
# bonus
#--------------------------------------------
CLIENT_SRC_BONUS	:=	$(COMMON_SRC) \
						client_bonus.c \
						send.c
SERVER_SRC_BONUS	:=	$(COMMON_SRC) \
						server_bonus.c

CLIENT_OBJS_BONUS	:=	$(CLIENT_SRC_BONUS:%.c=$(CLIENT_OBJ_DIR)/%.o)
SERVER_OBJS_BONUS	:=	$(SERVER_SRC_BONUS:%.c=$(SERVER_OBJ_DIR)/%.o)

ifeq ($(MAKECMDGOALS), bonus)
	CLIENT_OBJS		:=	$(CLIENT_OBJS_BONUS)
	SERVER_OBJS		:=	$(SERVER_OBJS_BONUS)
endif

#--------------------------------------------
# libft
#--------------------------------------------
LIBFT_DIR			:=	libft
LIBFT				:=	$(LIBFT_DIR)/libft.a

#--------------------------------------------
# include
#--------------------------------------------
INCLUDE_DIR			:=	include
INCLUDES			:=	-I$(LIBFT_DIR)/$(INCLUDE_DIR)/
DEPS				:=	$(CLIENT_OBJS:.o=.d) $(SERVER_OBJS:.o=.d)

#--------------------------------------------
# to do -> cc
CC					:=	cc
CFLAGS				:=	-Wall -Wextra -Werror -MMD -MP
MKDIR				:=	mkdir -p

#--------------------------------------------
all: $(CLIENT) $(SERVER)

bonus: all

-include $(DEPS)

$(LIBFT): FORCE
	$(MAKE) -C $(LIBFT_DIR)

#--------------------------------------------
$(CLIENT_OBJ_DIR)/%.o: $(CLIENT_SRC_DIR)/%.c
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR)/$(CLIENT_DIR)/ $(INCLUDES) -c $< -o $@ $(SLEEP_TIME)

$(SERVER_OBJ_DIR)/%.o: $(SERVER_SRC_DIR)/%.c
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR)/$(SERVER_DIR)/ $(INCLUDES) -c $< -o $@ $(SLEEP_TIME)

#--------------------------------------------
$(CLIENT): $(CLIENT_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(CLIENT_OBJS) $(LIBFT)

$(SERVER): $(SERVER_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(SERVER_OBJS) $(LIBFT)

#--------------------------------------------
clean:
	$(RM) -r $(OBJ_DIR) $(LIBFT_DIR)/$(OBJ_DIR)

fclean: clean
	$(RM) $(CLIENT) $(SERVER) $(LIBFT)

re: fclean all

#--------------------------------------------
norm:
	norminette

norm_ex_libft:
	norminette $(CLIENT_DIR) $(SERVER_DIR) $(INCLUDE_DIR)

slow:
	$(RM) -r $(CLIENT_OBJ_DIR) $(SERVER_OBJ_DIR)
	make SLEEP_TIME="-D SLEEP_TIME=5000"

FORCE:

info:
	$(info >>> default goal : $(.DEFAULT_GOAL))
	$(info >>> client obj : $(CLIENT_OBJS))
	$(info >>> server obj : $(SERVER_OBJS))

.PHONY: all clean fclean re bonus info FORCE norm norm_ex_libft slow
