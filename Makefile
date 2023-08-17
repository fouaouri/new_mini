NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror # -g3 -fsanitize=address

LIBFT = libs/libft
LIBS = $(addprefix $(LIBFT), /libft.a)

PARSING_SRC = parsing/
EXECUTION_SRC = execution/

PARSING_FILES = parsing.c mini_utils.c minishell.c mini_utils_2.c \
								sep_cmd.c counters.c expand_n.c ft_split.c \
								ft_count_quotes.c mini_utils_3.c help_clean.c \
								part_parsing.c #echo.c env.c libft_bonus.c redirections.c 

EXECUTION_FILES = check_cmd.c parse_path.c

PARSING_F_FILES = $(addprefix $(PARSING_SRC), $(PARSING_FILES))
EXECUTION_F_FILES	= $(addprefix $(EXECUTION_SRC), $(EXECUTION_FILES))

ALL_FILES = $(addprefix $(PARSING_SRC), $(PARSING_FILES)) \
						$(addprefix $(EXECUTION_SRC), $(EXECUTION_FILES))

PARSING_OBJ = $(PARSING_F_FILES:%.c=%.o)
EXECUTION_OBJ = $(EXECUTION_F_FILES:%.c=%.o)
O_FILES = $(addprefix $(PARSING_OBJ), $(EXECUTION_OBJ))

all: libft $(NAME)

libft:
	make -C $(LIBFT)

parsing: libft $(PARSING_OBJ)
	echo $(PARSING_OBJ)
	$(CC) $(CFLAGS) $(PARSING_OBJ) $(LIBS) -o pars

execution: libft $(EXECUTION_OBJ)
	$(CC) $(CFLAGS) $(EXECUTION_OBJ) $(LIBS) -o exec

$(NAME):
	$(CC) $(CFLAGS) $(ALL_FILES) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean : 
	@make clean -C $(LIBFT)
	rm -rf $(O_FILES)

fclean : clean
	@make fclean -C $(LIBFT)
	rm -rf $(NAME) exec pars

re : fclean $(NAME)
