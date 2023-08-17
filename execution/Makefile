NAME = exec
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

LIBFT = ../libs/libft/
LIBS = $(addprefix -L, $(LIBFT)/libft.a)

EXEC_FILES = check_cmd.c parse_path.c

OBJF = $(EXEC_FILES:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJF)
	@make -C $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJF) $(LIBS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C $(LIBFT) clean  
	$(RM) $(OBJF)

fclean: clean
	@make -C $(LIBFT) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
