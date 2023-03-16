CLIENT				:=	client
SERVER				:=	server

#------------------------------------------------------
# mandatory
CLIENT_DIR			:=	src_client
SERVER_DIR			:=	src_server

CLIENT_SRC			:=	client.c
SERVER_SRC			:=	server.c

#------------------------------------------------------
# bonus
COMMON_SRC			:=	error.c \
						put_stderr.c\
# ok..?
ifeq ($(MAKECMDGOALS), bonus)
	CLIENT_SRC		:= client_bonus.c $(COMMON_SRC)
	SERVER_SRC		:= server_bonus.c $(COMMON_SRC)
endif

#------------------------------------------------------
# obj
CLIENT_OBJ_DIR		:=	obj_client
SERVER_OBJ_DIR		:=	obj_server

CLIENT_OBJ			:=	$(CLIENT_SRC:%.c=$(CLIENT_OBJ_DIR)/%.o)
SERVER_OBJ			:=	$(SERVER_SRC:%.c=$(SERVER_OBJ_DIR)/%.o)

#------------------------------------------------------
# libft
LIBFT_DIR			:=	libft
LIBFT				:=	$(LIBFT_DIR)/libft.a
OBJ_DIR				:=	obj

#------------------------------------------------------
# include
INCLUDE_DIR			:=	include
INCLUDES			:=	-I. -I$(INCLUDE_DIR) -I$(LIBFT_DIR)/$(INCLUDE_DIR)/
DEPS				:=	$(OBJS:.o=.d)

#------------------------------------------------------
# to do -> cc
CC					:=	clang
CFLAGS				:=	-Wall -Wextra -Werror -MMD -MP
MKDIR				:=	mkdir -p

all: $(CLIENT) $(SERVER)

bonus: all

-include $(DEPS)

$(LIBFT): FORCE
	$(MAKE) -C $(LIBFT_DIR)

#------------------------------------------------------
$(CLIENT_OBJ_DIR)/%.o: $(CLIENT_DIR)/%.c
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

$(SERVER_OBJ_DIR)/%.o: $(SERVER_DIR)/%.c
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

#------------------------------------------------------
$(CLIENT): $(CLIENT_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(CLIENT_OBJ) $(LIBFT)

$(SERVER): $(SERVER_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(SERVER_OBJ) $(LIBFT)

#------------------------------------------------------
clean:
	$(RM) -r $(CLIENT_OBJ_DIR) $(SERVER_OBJ_DIR) $(LIBFT_DIR)/$(OBJ_DIR)

fclean: clean
	$(RM) $(CLIENT) $(SERVER) $(LIBFT)

re: fclean all

#------------------------------------------------------
norm:
	norminette

norm_ex_libft:
	norminette $(CLIENT_DIR) $(SERVER_DIR) $(INCLUDE_DIR)

FORCE:

$(info >>> default goal : $(.DEFAULT_GOAL))
$(info >>> client src : $(CLIENT_SRC))
$(info >>> server src : $(SERVER_SRC))
$(info >>> client obj : $(CLIENT_OBJ))
$(info >>> server obj : $(SERVER_OBJ))

.PHONY: all clean fclean re bonus info FORCE norm norm_ex_libft
