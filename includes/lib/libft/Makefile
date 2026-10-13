# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chguerre <chguerre@student.lausanne.ch>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/19 23:39:11 by chguerre          #+#    #+#              #
#    Updated: 2026/04/11 14:48:20 by chguerre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	 = libft.a
CC		 = cc
CFLAGS	= -Wall -Wextra -Werror
INC_DIR  = includes
OBJ_DIR  = objects
SRCS_DIR = srcs

INCLUDES = -I $(INC_DIR)

LIBFT_DIR = $(SRCS_DIR)/libft

LIBFT_FILES= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
			ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
			ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
			ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
			ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
			ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

PRINTF_DIR= $(SRCS_DIR)/printf
PRINTF_FILES= ft_print_xX.c ft_printarg.c ft_printf.c ft_putchar_counter.c \
			ft_putnbr_counter.c ft_putnbr_unsigned.c ft_putpointer.c ft_putstr_counter.c

GNL_DIR= $(SRCS_DIR)/get_next_line
GNL_FILE= get_next_line_utils.c get_next_line.c


SRCS = $(addprefix $(LIBFT_DIR)/, $(LIBFT_FILES)) \
		$(addprefix $(PRINTF_DIR)/, $(PRINTF_FILES)) \
		$(addprefix $(GNL_DIR)/, $(GNL_FILE))

OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJ_DIR)/%.o)

RM			= rm -f
AR			= ar rcs

all:			$(NAME)

$(NAME):		$(OBJS)
					@echo "Creando libreria $(NAME) ..."
					@$(AR) $(NAME) $(OBJS)
					@echo "libreria creada con exito"
$(OBJ_DIR)/%.o:	$(SRCS_DIR)/%.c
					@mkdir -p $(dir $@)
					@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(RM) -rf $(OBJ_DIR)
	@echo "Objetos eliminados 🗑️"

fclean: clean
	@$(RM) $(NAME)
	@echo "Libreria $(NAME) eliminada 🗑️"

re: fclean all