NAME = executor
CC = cc -g
CFLAGS = -Werror -Wextra -Wall -I$(LIBFT_INC) -Iincludes 

SRC_DIR = src
SRCS		= $(SRC_DIR)/executor/executor.c \
				$(SRC_DIR)/main/main.c
OBJ_DIR		= objs
OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o)

UTILS_DIR = utils
#UTILS = $(UTILS_DIR)/cleaner.c 
#		$(UTILS_DIR)/parsing_pipex.c
UTILS_OBJ	= $(addprefix $(OBJ_DIR)/, $(notdir $(UTILS:.c=.o)))


LIBFT_DIR = includes/lib/libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INC = $(LIBFT_DIR)/includes
LIBFT_LIB = -L$(LIBFT_DIR) -lft

#Reglas 👽

all: $(OBJ_DIR) $(NAME) 
$(OBJ_DIR) :
	@mkdir -p $(OBJ_DIR)
	@echo "Directorio objetos creado con exito."

$(NAME) :  $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(UTILS_OBJ) $(LIBFT) $(LIBFT_LIB) -o $(NAME) -lreadline
	@echo "✨ Voilà executor está listo." 

$(LIBFT):
	@echo "🔨 Construyendo libft..."
	@make -C $(LIBFT_DIR)
	@echo "libft construida con éxito."
	
$(OBJ_DIR)/%.o: $(UTILS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	@echo "!borrando objetos"
	@rm -rf $(OBJ_DIR) $(UTILS_OBJ)
	@rm -rf $(LIBFT_DIR)/objects

fclean: clean
	@echo "borrando ejecutable"
	@rm -rf $(NAME)
	@rm -rf $(LIBFT_DIR)/libft.a

re: fclean all

.PHONY:  all clean fclean re
