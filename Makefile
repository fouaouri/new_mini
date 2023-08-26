NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address

LIBFT = libs/libft
LIBS = $(addprefix $(LIBFT), /libft.a)

PARSING_SRC = parsing/
BUILTINS_SRC = builtins/
EXECUTION_SRC = execution/

EXECUTION_FILES = check_cmd.c parse_path.c test.c heredoc.c \
									handle_files.c ft_errors.c open_pipes.c \
									exec_utils.c

BUILTINS_FILES = exit.c

PARSING_FILES = parsing.c mini_utils.c minishell.c mini_utils_2.c \
								sep_cmd.c counters.c expand_n.c ft_split.c \
								ft_count_quotes.c mini_utils_3.c help_clean.c part_parsing.c \

# echo.c env.c libft_bonus.c redirections.c 


PARSING_F_FILES = $(addprefix $(PARSING_SRC), $(PARSING_FILES))
BUILTINS_F_FILES = $(addprefix $(BUILTINS_SRC), $(BUILTINS_FILES))
EXECUTION_F_FILES	= $(addprefix $(EXECUTION_SRC), $(EXECUTION_FILES))

ALL_FILES = $(addprefix $(PARSING_SRC), $(PARSING_FILES)) \
						$(addprefix $(EXECUTION_SRC), $(EXECUTION_FILES)) \
						$(addprefix $(BUILTINS_SRC), $(BUILTINS_FILES))

PARSING_OBJ = $(PARSING_F_FILES:%.c=%.o)
EXECUTION_OBJ = $(EXECUTION_F_FILES:%.c=%.o)

O_FILES = $(PARSING_F_FILES:%.c=%.o)
O_FILES += $(EXECUTION_F_FILES:%.c=%.o)
O_FILES += $(BUILTINS_F_FILES:%.c=%.o)

all: $(NAME)

$(NAME): libft $(O_FILES)
	@$(CC) -lreadline $(CFLAGS) $(ALL_FILES) $(LIBS) -o $(NAME)

libft:
	@make -C $(LIBFT)

parsing: libft $(PARSING_OBJ)
	@$(CC) -lreadline $(CFLAGS) $(PARSING_OBJ) $(LIBS) -o pars

execution: libft $(EXECUTION_OBJ)
	@$(CC) $(CFLAGS) $(EXECUTION_OBJ) $(LIBS) -o exec


%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean : 
	@cd $(LIBFT) && make clean
	@rm -rf $(PARSING_OBJ) $(EXECUTION_OBJ) $(O_FILES)

fclean : clean
	@cd $(LIBFT) && make fclean
	@rm -rf $(NAME) exec pars

re : fclean all
