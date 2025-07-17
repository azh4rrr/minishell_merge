# Colors
BOLD	= \033[1m
GREEN	= \033[32;1m
BLUE	= \033[34;1m
YELLOW	= \033[33;1m
RED		= \033[31;1m
CYAN	= \033[36;1m
RESET	= \033[0m

# Compiler and flags
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RFLG	= -lreadline -lncurses
NAME	= minishell
READLINE_DIR = $(shell brew --prefix readline)
LIB		= ./libft/libft.a

# Source files

SRC =	minishell.c										\
		./parsing/parsing.c								\
		./parsing/redirecting/parse_redir.c 			\
		./parsing/redirecting/parse_redir_utils.c 		\
		./parsing/redirecting/parse_redir_utils_b.c 	\
		./parsing/redirecting/redirection.c 			\
		./parsing/utils/utils_a.c 						\
		./parsing/utils/utils_b.c 						\
		./parsing/utils/utils_c.c 						\
		./parsing/expansion/expansion.c 				\
		./parsing/expansion/expansion_utils.c 			\
		./parsing/expansion/expansion_utils_b.c 		\
		./parsing/special_split.c 						\
		./parsing/syntax_handle.c 						\
		./execution/builtin/built_in.c					\
		./execution/builtin/cd.c						\
		./execution/builtin/unset.c						\
		./execution/builtin/echo.c						\
		./execution/builtin/exit.c						\
		./execution/builtin/export.c					\
		./execution/builtin/export_utils.c				\
		./execution/execution.c							\
		./execution/fork.c								\
		./execution/get_next_line.c						\
		./execution/redirections.c						\
		./execution/utils_std.c							\
		./execution/get_path.c							\
		./execution/heredoc.c							\
		./execution/error.c								\
		./execution/signals.c							\
		./execution/environment.c						\
		./execution/environment_utils.c					\
		./execution/list_utils.c						\
		./execution/leaks_mem.c							\
		./execution/leaks_fd.c							\
		./execution/exit_status.c						\
		./EVP/env_expander.c							\
		./EVP/env_heredoc.c								\
		./EVP/env_leaks.c								\
		./EVP/exp_special.c								\
		./EVP/utils_env.c								\

HDR =	minishell.h										\
		./parsing/include/syntax.h						\

OBJ = $(SRC:.c=.o)

all: libft $(NAME)

libft:
	@echo "$(CYAN)$(BOLD)📚 COMPILING LIBFT...$(RESET)"
	@$(MAKE) -C ./libft
	@echo "$(GREEN)$(BOLD)✅ LIBFT COMPILED!$(RESET)\n"

$(NAME): $(OBJ) $(LIB)
	@echo "$(CYAN)$(BOLD)🔗 LINKING $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIB) -I$(READLINE_DIR)/include -L$(READLINE_DIR)/lib -o $@ $(RFLG)
	@echo "$(GREEN)$(BOLD)🎉 SUCCESS: $(NAME) READY!$(RESET)\n"

%.o: %.c $(HDR)
	@case "$<" in \
		*parsing*) \
			echo "$(YELLOW)🧩 [Parsing] Compiling:\t$<$(RESET)";; \
		*execution*) \
			echo "$(BLUE)⚡ [Execution] Compiling:\t$<$(RESET)";; \
	esac
	@$(CC) $(CFLAGS) -I$(READLINE_DIR)/include -c $< -o $@

clean:
	@echo "$(RED)$(BOLD)🧹 CLEANING OBJECT FILES...$(RESET)"
	@rm -f $(OBJ)
	@$(MAKE) -C ./libft clean
	@echo "$(GREEN)$(BOLD)✅ OBJECTS CLEANED!$(RESET)\n"

fclean: clean
	@echo "$(RED)$(BOLD)🧹 REMOVING $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -C ./libft fclean
	@echo "$(GREEN)$(BOLD)✅ FULL CLEAN COMPLETE!$(RESET)\n"

re: fclean all

.PHONY: all libft clean fclean re
