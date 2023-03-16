SRCS_LIBFT	:=	libft/ft_atoi_with_bool.c \
				libft/ft_atoi.c \
				libft/ft_bzero.c \
				libft/ft_calloc.c \
				libft/ft_isalnum.c \
				libft/ft_isalpha.c \
				libft/ft_isascii.c \
				libft/ft_isdigit.c \
				libft/ft_isprint.c \
				libft/ft_itoa_int.c \
				libft/ft_itoa.c \
				libft/ft_max.c \
				libft/ft_memchr.c \
				libft/ft_memcmp.c \
				libft/ft_memcpy.c \
				libft/ft_memmove.c \
				libft/ft_memset.c \
				libft/ft_min.c \
				libft/ft_putchar_fd.c \
				libft/ft_putendl_fd.c \
				libft/ft_putnbr_fd.c \
				libft/ft_putstr_fd.c \
				libft/ft_split.c \
				libft/ft_strchr.c \
				libft/ft_strdup.c \
				libft/ft_striteri.c \
				libft/ft_strjoin.c \
				libft/ft_strlcat.c \
				libft/ft_strlcpy_void.c \
				libft/ft_strlcpy.c \
				libft/ft_strlen.c \
				libft/ft_strmapi.c \
				libft/ft_strncmp.c \
				libft/ft_strndup.c \
				libft/ft_strnlen.c \
				libft/ft_strnstr.c \
				libft/ft_strrchr.c \
				libft/ft_strtrim.c \
				libft/ft_substr.c \
				libft/ft_tolower.c \
				libft/ft_toupper.c

SRCS_LIST	:=	libft/ft_lstadd_back.c \
				libft/ft_lstadd_front.c \
				libft/ft_lstclear.c \
				libft/ft_lstdelone.c \
				libft/ft_lstiter.c \
				libft/ft_lstlast.c \
				libft/ft_lstmap.c \
				libft/ft_lstnew.c \
				libft/ft_lstsize.c

SRC_FT_PRINTF	:=	ft_printf/convert_to_str.c \
					ft_printf/convert_to_str2.c \
					ft_printf/ft_printf.c \
					ft_printf/handle_info.c \
					ft_printf/itoa_utoa_for_printf.c\
					ft_printf/parse_format.c \
					ft_printf/ptoa_xtoa_for_printf.c \
					ft_printf/set_field.c \
					ft_printf/set_output.c \
					ft_printf/strdup_for_printf.c

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
SRCS		:=	$(SRC_FT_PRINTF) $(SRC_FT_DPRINTF) $(SRCS_LIBFT) $(SRCS_LIST)
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
