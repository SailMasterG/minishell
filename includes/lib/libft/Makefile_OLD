# NAME = libft.a
# CC = cc
# CFLAGS = -Wall -Wextra -Werror
# HEADERS = libft.h

# # Archivos base
# SRCS = ft_isalpha.c \
# 	ft_isdigit.c \
# 	ft_isalnum.c \
# 	ft_isascii.c \
# 	ft_isprint.c \
# 	ft_strlen.c \
# 	ft_memset.c \
# 	ft_bzero.c \
# 	ft_memcpy.c \
# 	ft_memmove.c \
# 	ft_strlcpy.c \
# 	ft_strlcat.c \
# 	ft_toupper.c \
# 	ft_tolower.c \
# 	ft_strchr.c \
# 	ft_strrchr.c \
# 	ft_strncmp.c \
# 	ft_memchr.c \
# 	ft_memcmp.c \
# 	ft_strnstr.c \
# 	ft_atoi.c \
# 	ft_calloc.c \
# 	ft_strdup.c \
# 	ft_substr.c \
# 	ft_strjoin.c \
# 	ft_strtrim.c \
# 	ft_split.c \
# 	ft_itoa.c \
# 	ft_strmapi.c \
# 	ft_striteri.c \
# 	ft_putchar_fd.c \
# 	ft_putstr_fd.c \
# 	ft_putendl_fd.c \
# 	ft_putnbr_fd.c

# # Archivos bonus
# SRCS_BONUS = ft_lstnew.c \
# 	ft_lstadd_front.c \
# 	ft_lstsize.c \
# 	ft_lstlast.c \
# 	ft_lstadd_back.c \
# 	ft_lstdelone.c \
# 	ft_lstclear.c \
# 	ft_lstiter.c \
# 	ft_lstmap.c

# # Objetos
# OBJS = $(SRCS:.c=.o)
# OBJS_BONUS = $(SRCS_BONUS:.c=.o)

# # Regla por defecto
# all: $(NAME)

# # Crear la librería con archivos normales
# $(NAME): $(OBJS)
# 	ar rcs $(NAME) $(OBJS)
# 	ranlib $(NAME)

# # Bonus: compilar primero los objetos bonus, luego agregarlos a la librería
# bonus : $(OBJS_BONUS)
# # Compilación de cada objeto
# %.o: %.c $(HEADERS)
# 	$(CC) $(CFLAGS) -I. -c $< -o $@

# # Limpiar objetos
# clean:
# 	rm -f $(OBJS) $(OBJS_BONUS)

# # Limpiar todo
# fclean: clean
# 	rm -f $(NAME)

# # Reconstruir todo
# re: fclean all

# .PHONY: all clean fclean re bonus
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lalamino <lalamino@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/01 10:19:17 by lalamino          #+#    #+#              #
#    Updated: 2025/12/09 10:56:05 by lalamino         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME = libft.a
# SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
# 	ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
# 	ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
# 	ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
# 	ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
# 	ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
# 	ft_putendl_fd.c ft_putnbr_fd.c
# BONUS_SRC = ft_lstadd_frond.c lst_add_back.c ft_lstclear.c \
# 	ft__lstdelone.c ft_lstiter.c ft_lstlast.c \
# 	lstmap.c ft_lstnew.c ft_lstsize.c
# CC = gcc
# CFLAGS = -Wall -Wextra -Werror
# AR = ar rcs
# OBJECTS = $(SRC:.c=.o)
# OBJECTS_BONUS = $(BONUS_SRC:.c=.0)

# all:$(NAME)

# $(NAME):$(OBJECTS) 
# 	$(AR) $@ $^

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# clean :
# 	rm -f *.o

# fclean : clean
# 	rm -f $(NAME)

# re : fclean all

SOURCES			=	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
	ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
	ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
	ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
	ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c

SOURCES_BONUS	=	ft_lstadd_front.c ft_lstadd_back.c ft_lstclear.c \
	ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
	ft_lstmap.c ft_lstnew.c ft_lstsize.c

HEADER			=	libft.h

OBJ_DIR			=	objects

OBJECTS			=	$(SOURCES:%.c=$(OBJ_DIR)/%.o)
OBJECTS_BONUS	=	$(SOURCES_BONUS:%.c=$(OBJ_DIR)/%.o)

NAME			=	libft.a
NAME_BONUS		=	libft_bonus.a

CC				=	clang
AR				=	ar
RM				=	rm -rf

CFLAGS			=	-Wall -Wextra -Werror
ARFLAGS 		=	rcs

$(OBJ_DIR)/%.o:		%.c $(HEADER)
					$(CC) $(CFLAGS) -c $< -o $@

all:				$(NAME)

bonus:				$(NAME_BONUS)

$(NAME):			$(OBJ_DIR) $(OBJECTS) $(HEADER)
					$(AR) $(ARFLAGS) $(NAME) $(OBJECTS)

$(NAME_BONUS):		$(NAME) $(OBJ_DIR) $(OBJECTS_BONUS) $(HEADER)
					$(AR) $(ARFLAGS) $(NAME) $(OBJECTS_BONUS)
					cp $(NAME) $(NAME_BONUS)

$(OBJ_DIR):
					mkdir -p $(OBJ_DIR)

clean:
					$(RM) $(OBJ_DIR)

fclean:				clean
					$(RM) $(NAME) $(NAME_BONUS)

re:					fclean all

.PHONY:				all clean fclean re bonus