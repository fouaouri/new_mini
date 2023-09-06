NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror  -g3 -fsanitize=address
LIBFT = libs/libft
LIBS = $(addprefix $(LIBFT), /libft.a)

PARSING_SRC = parsing/
BUILTINS_SRC = builtins/
EXECUTION_SRC = execution/

EXECUTION_FILES = check_cmd.c parse_path.c test.c heredoc.c \
									handle_files.c ft_errors.c open_pipes.c \
									exec_utils.c execution_flow.c free_utils.c \
									signals_handlers.c

BUILTINS_FILES = exit.c ft_export.c ft_env.c ft_unset.c

PARSING_FILES = parsing.c mini_utils.c minishell.c mini_utils_2.c \
								sep_cmd.c counters.c expand_n.c ft_split.c \
								ft_count_quotes.c mini_utils_3.c help_clean.c part_parsing.c parse_env.c \

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

SILENT = @

all: $(NAME)

$(NAME): libft $(O_FILES)
	$(SILENT) $(CC) $(CFLAGS) $(ALL_FILES) $(LIBS) -lreadline -o $(NAME)

libft:
	$(SILENT)	cd $(LIBFT) && make

parsing: libft $(PARSING_OBJ)
	$(SILENT) $(CC) -lreadline $(CFLAGS) $(PARSING_OBJ) $(LIBS) -o pars

execution: libft $(EXECUTION_OBJ)
	$(SILENT) $(CC) $(CFLAGS) $(EXECUTION_OBJ) $(LIBS) -o exec


%.o: %.c
	$(SILENT) $(CC) $(CFLAGS) -lreadline -c $< -o $@

clean : 
	$(SILENT) cd $(LIBFT) && make clean
	$(SILENT) rm -rf $(PARSING_OBJ) $(EXECUTION_OBJ) $(O_FILES)

fclean : clean
	$(SILENT) cd $(LIBFT) && make fclean
	$(SILENT) rm -rf $(NAME) exec pars

re : fclean all
