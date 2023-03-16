#--------------------------------------------
# target
#--------------------------------------------
CLIENT				:=	client
SERVER				:=	server

#--------------------------------------------
# common
#--------------------------------------------
COMMON_SRC			:=	error.c \
						put.c

#--------------------------------------------
# obj dir
#--------------------------------------------
CLIENT_OBJ_DIR		:=	obj_client
SERVER_OBJ_DIR		:=	obj_server

#--------------------------------------------
# mandatory
#--------------------------------------------
CLIENT_DIR			:=	src_client
SERVER_DIR			:=	src_server

CLIENT_SRC			:=	client.c $(COMMON_SRC)
SERVER_SRC			:=	server.c $(COMMON_SRC)

# ifeq ($(MAKECMDGOALS), bonus)
# 	CLIENT_SRC		:= client_bonus.c $(COMMON_SRC)
# 	SERVER_SRC		:= server_bonus.c $(COMMON_SRC)
# endif

CLIENT_OBJS			:=	$(CLIENT_SRC:%.c=$(CLIENT_OBJ_DIR)/%.o)
SERVER_OBJS			:=	$(SERVER_SRC:%.c=$(SERVER_OBJ_DIR)/%.o)

#--------------------------------------------
# bonus
#--------------------------------------------
CLIENT_SRC_BONUS	:=	client_bonus.c $(COMMON_SRC) \
						args.c \
						recieve.c \
						send.c \
						signal.c
SERVER_SRC_BONUS	:=	server_bonus.c $(COMMON_SRC)

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
OBJ_DIR				:=	obj

#--------------------------------------------
# include
#--------------------------------------------
INCLUDE_DIR			:=	include
INCLUDES			:=	-I. -I$(LIBFT_DIR)/$(INCLUDE_DIR)/
DEPS				:=	$(CLIENT_OBJS:.o=.d) $(SERVER_OBJS:.o=.d)

#--------------------------------------------
# to do -> cc
CC					:=	cc
CFLAGS				:=	-Wall -Wextra -Werror -MMD -MP
MKDIR				:=	mkdir -p

all: $(CLIENT) $(SERVER)

bonus: all

-include $(DEPS)

$(LIBFT): FORCE
	$(MAKE) -C $(LIBFT_DIR)

#--------------------------------------------
$(CLIENT_OBJ_DIR)/%.o: $(CLIENT_DIR)/%.c
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(SERVER_OBJ_DIR)/%.o: $(SERVER_DIR)/%.c
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

#--------------------------------------------
$(CLIENT): $(CLIENT_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(CLIENT_OBJS) $(LIBFT)

$(SERVER): $(SERVER_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(SERVER_OBJS) $(LIBFT)

#--------------------------------------------
clean:
	$(RM) -r $(CLIENT_OBJ_DIR) $(SERVER_OBJ_DIR) $(LIBFT_DIR)/$(OBJ_DIR)

fclean: clean
	$(RM) $(CLIENT) $(SERVER) $(LIBFT)

re: fclean all

#--------------------------------------------
norm:
	norminette

norm_ex_libft:
	norminette $(CLIENT_DIR) $(SERVER_DIR) $(INCLUDE_DIR)

FORCE:

$(info >>> default goal : $(.DEFAULT_GOAL))
$(info >>> client obj : $(CLIENT_OBJS))
$(info >>> server obj : $(SERVER_OBJS))

.PHONY: all clean fclean re bonus info FORCE norm norm_ex_libft
