INC_DIR := includes/
SRC_DIR	:= srcs/
OBJ_DIR	:= objs/
OBJ_DIRS = $(OBJ_DIR)


MINISHELL_PRE_SRCS = 	main utils_strsjoin utils free token_parser token \
						token_delimiter token_pipe token_cmd token_input \
						token_trunc exec_token token_append cmd_split \
						cmd_treat cmd_exec cmd_echo cmd_path cmd_cd \
						cmd_cd_fictif cmd_env cmd_exit env_utils env_set env_init_free env_print \
						utils_space init readline utils2 cmd_path_fd env_set2 env_unset
MINISHELL_SRCS = $(addsuffix .c, $(addprefix $(SRC_DIR), $(MINISHELL_PRE_SRCS)))
MINISHELL_OBJS = $(addsuffix .o, $(addprefix $(OBJ_DIR), $(MINISHELL_PRE_SRCS)))

MINISHELL_NAME := minishell

CC := gcc
CFLAGS := -Wall -Werror -Wextra
INC	:= -I./$(INC_DIR) -I/Users/$(USER)/.brew/opt/readline/include
RM = rm -f

all:	$(MINISHELL_NAME)

$(MINISHELL_NAME): lib $(OBJ_DIRS) $(MINISHELL_OBJS)
	$(CC) $(CFLAGS) $(MINISHELL_OBJS) -lreadline -lncurses libft.a libftprintf.a -L /Users/$(USER)/.brew/opt/readline/lib -o $(MINISHELL_NAME) 
	echo "----- \033[32m $@ compiled\033[0m  -----"

$(OBJ_DIRS):
	mkdir -p $(OBJ_DIRS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c includes/minishell.h
	$(CC) $(CFLAGS) $(INC) -c $< -o $@
	echo "$@ \033[32mcreated\033[0m"

lib:
	make -C libft/printf
	echo "----- \033[32m printf compiled\033[0m  -----"
	make -C libft
	make bonus -C libft
	echo "----- \033[32m libft compiled\033[0m  -----"
	cp libft/printf/libftprintf.a ./
	cp libft/libft.a ./

clean:
	rm -rf $(OBJ_DIR)
	make -C libft clean
	rm -f /libs/libftprintf.a
	rm -f /libs/libft.a

fclean: 	clean
	rm -f $(MINISHELL_NAME)
	rm -f libft.a
	rm -f libftprintf.a
	make -C libft fclean
re:		fclean all
.PHONY : all clean fclean re
.SILENT :
