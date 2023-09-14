NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
LIBFT = libs/libft
LIBS = $(addprefix $(LIBFT), /libft.a)

PARSING_SRC = parsing/
BUILTINS_SRC = builtins/
EXECUTION_SRC = execution/

EXECUTION_FILES = check_cmd.c parse_path.c test.c heredoc.c \
									handle_files.c ft_errors.c open_pipes.c \
									exec_utils.c execution_flow.c free_utils.c \
									signals_handlers.c mini_utils.c pipe_utils.c handle_files_utils.c \

BUILTINS_FILES = ft_exit.c ft_export.c ft_env.c ft_unset.c ft_pwd.c ft_echo.c ft_cd.c

PARSING_FILES = parsing.c mini_utils.c minishell.c mini_utils_2.c syntax_err1.c syntax_err.c syntax_err2.c \
								sep_cmd.c counters.c expand_n.c expand.c if_expand.c init_quotes.c\
								ft_count_quotes.c help_clean.c part_parsing.c parse_env.c init_quotes1.c \

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

all: libft $(NAME)

$(NAME): $(O_FILES)
	$(SILENT) $(CC) $(CFLAGS) $(ALL_FILES) $(LIBS) -lreadline -o $(NAME)

libft:
	$(SILENT)	cd $(LIBFT) && make

%.o: %.c
	$(SILENT) $(CC) $(CFLAGS) -lreadline -c $< -o $@

clean : 
	$(SILENT) cd $(LIBFT) && make clean
	$(SILENT) rm -rf $(O_FILES)

fclean : clean
	$(SILENT) cd $(LIBFT) && make fclean
	$(SILENT) rm -rf $(NAME) exec pars

re : fclean all
