NAME = minishell
CC = gcc
src = parsing.c mini_utils.c minishell.c mini_utils_2.c \
			sep_cmd.c counters.c expand_n.c ft_split.c \
 			ft_count_quotes.c mini_utils_3.c help_clean.c \
			part_parsing.c #echo.c env.c libft_bonus.c redirections.c 

LIBFT = ../libs/libft/
LIBS = $(addprefix $(LIBFT), libft.a)

O_files = $(src:.c=.o)
CFLAGS = -Wall -Wextra -Werror # -fsanitize=address -g3

all: libft $(NAME)

libft:
	@make -C $(LIBFT)

$(NAME) : $(O_files)
	$(CC) $(CFLAGS) $(O_files) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean : 
	rm -rf $(O_files)

fclean : clean
	rm -rf $(NAME)

re : fclean $(NAME)
