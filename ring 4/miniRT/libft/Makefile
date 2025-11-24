# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cprot <cprot@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 22:51:05 by scavalli          #+#    #+#              #
#    Updated: 2025/11/19 16:13:26 by cprot            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
       ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c \
       ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c \
       ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c \
       ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_strcmp.c \
       ft_lentab.c ft_atof.c

ADDITIONAL = ft_itoa.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
             ft_putstr_fd.c ft_split.c ft_strjoin.c ft_strmapi.c \
             ft_strtrim.c ft_substr.c ft_striteri.c

BONUS = ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c \
        ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c \
        ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c

GNL = get_next_line.c get_next_line_utils.c

PRINTF = ft_printf.c ft_putnbr_printf.c ft_putnbr_hex_printf.c \
         ft_putptr_hex_printf.c ft_putstr_printf.c

NAME = libft.a
CC = clang
CFLAGS = -Wall -Wextra -Werror

SRCS = $(LIBC) $(ADDITIONAL) $(GNL) $(PRINTF)
SRCS_BONUS = $(BONUS)

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

.SILENT:

.PHONY: all clean fclean re bonus

all: $(NAME) bonus

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

bonus: $(OBJS_BONUS)
	ar rsc $(NAME) $(OBJS_BONUS)

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all