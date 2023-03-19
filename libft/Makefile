SRCS_LIBFT	:=	libft/ft_atoi_with_bool.c \
				libft/ft_isdigit.c \
				libft/ft_max.c \
				libft/ft_memset.c \
				libft/ft_strchr.c \
				libft/ft_toupper.c

SRC_FT_DPRINTF	:=	ft_dprintf/convert_to_str.c \
					ft_dprintf/convert_to_str2.c \
					ft_dprintf/ft_dprintf.c \
					ft_dprintf/handle_info.c \
					ft_dprintf/itoa_utoa_for_printf.c\
					ft_dprintf/parse_format.c \
					ft_dprintf/ptoa_xtoa_for_printf.c \
					ft_dprintf/set_field.c \
					ft_dprintf/set_output.c \
					ft_dprintf/strdup_for_printf.c

NAME		:=	libft.a

SRC_DIR		:=	src
OBJ_DIR		:=	obj
SRCS		:=	$(SRC_FT_DPRINTF) $(SRCS_LIBFT)
OBJS		:=	$(SRCS:%.c=$(OBJ_DIR)/%.o)

INCLUDE_DIR	:=	include
INCLUDES	:=	-I./$(INCLUDE_DIR)/

DEPS		:=	$(OBJS:.o=.d)

# or cc
CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror -MMD -MP
ARFLAGS		:=	rcs
MKDIR		:=	mkdir -p

all: $(NAME)

-include $(DEPS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
