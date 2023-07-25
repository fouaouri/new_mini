src = parsing.c cd.c unset.c export.c exit.c pwd.c mini_utils.c minishell.c mini_utils_2.c sep_cmd.c counters.c expand_n.c ft_split.c\
	ft_count_quotes.c mini_utils_3.c help_clean.c part_parsing.c atoi_itoi.c #echo.c env.c libft_bonus.c redirections.c 

O_files = $(src:.c=.o)
CFLAGS = -Wall -Wextra -Werror -fsanitize=address 

NAME = minishell

$(NAME) : $(O_files)
	gcc -lreadline $(CFLAGS) $(O_files)   -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean : 
	rm -rf $(O_files) $(bonus_O)

fclean : clean
	rm -rf $(NAME)

re : fclean $(NAME)
