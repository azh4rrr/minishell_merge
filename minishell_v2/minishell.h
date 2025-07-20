/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhar <azhar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:19:12 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/20 22:09:00 by azhar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>

# define OPEN_FAILD "minishell open faild"
# define DUP_FAILD "minishell dup faild"
# define HERDOC_FAILD "minishell herdoc"
# define JOIN_FAILD "minishell join faild"
# define FORK_FAILD "minishell fork faild"
# define GET_LINE "minishell get next line faild"
# define ERR_MEM "minishell alloc"

extern int				exit_status;
typedef enum s_type
{
	WORD,
	PIPE,
	ENV,
	D_OUTFILE,
	D_APPEND,
	D_INFILE,
	D_HERDOC,
	D_HERDOC_Q
}						t_type;

typedef struct s_split
{
	char				*str;
	char				delimiter;
	int					i;
	int					start;
	int					token_idx;
	int					token_count;
	int					in_single;
	int					in_double;
	char				**tokens;
}						t_split;

typedef struct s_splt
{
	char				**tokens;
	int					i;
	int					token_idx;
	int					start;
	int					in_single;
	int					in_double;
}						t_splt;

typedef struct s_amb
{
	bool				d_quotes;
	bool				s_quotes;
	bool				ambiguous;
	int					r;
}						t_ambg;

typedef struct s_token
{
	char				*content;
	bool				red;
	bool				exp;
	bool				amb;
	t_type				type_token;
	struct s_token		*next;
}						t_token;

typedef struct s_redirec
{
	char				*name;// $v
	t_type				type; // AMG
	struct s_redirec	*next;
}						t_redirec;

typedef struct s_cmd
{
	char				**cmd;
	bool				amb;
	t_redirec			*redirec;
	int					fd_herdoc[2];
	int					fd_io[2];
	int					fd_pip[2];
	struct s_cmd		*next;
	struct s_cmd		*prev;
}						t_cmd;

typedef struct s_exp
{
	char				*result;
	int					i;
	int					j;
	int					res;
	int					var_len;
	char				*var_name;
	char				*expanded;
	int					in_single;
	int					in_double;
}						t_exp;

typedef struct s_paredir
{
	int					i;
	int					start;
	int					end;
	char				*first_token;
	int					result;
	char				quote;
}						t_paredir;

typedef struct s_shell
{
	t_cmd				*list; //
	t_list				*env; //
	int					std_backup[2];
	int					exit_status;
}						t_shell; //

typedef struct s_spl
{
	int					i;
	int					r;
	bool				f_quotes;
	char				*new_token;
}						t_spl;

typedef struct s_refactor
{
	char				*new;
	char				quotes;
	int					r;
	int					f;
	bool				flag;
}						t_refactor;

typedef struct s_norm
{
	int					r;
	int					pipe;
}						t_norm;

typedef struct s_cm
{
	int					size;
	int					r;
	int					i;
}						t_cm;

typedef struct s_cm1
{
	t_redirec			*new_red;
	t_redirec			*tmp_red;
}						t_cm1;

typedef struct s_expa
{
	int					r;
	int					len_key;
	int					len_value;
	char				*value;
	char				*key;
}						t_expa;

typedef struct s_p_exp
{
	int					i;
	int					j;
	int					changed;
	size_t				len;
	char				*result;
}						t_p_exp;

/*Colors*/
# define COLORE_RESET "\033[0m"
# define COLORE_RED "\033[31m"
# define COLORE_GREEN "\033[32m"
# define COLORE_YELLOW "\033[33m"
# define COLORE_BLUE "\033[34m"
# define COLORE_MAGENTA "\033[35m"
# define COLORE_CYAN "\033[36m"

//! ============================================================================
//!  							PARSING PHASE
//! ============================================================================

/* The main parsing function */

int						parse_commands(char *line, t_shell *var);
int						parse_input(char *line, t_shell *var);
char					*pre_expand_line_if_needed(char *line, t_shell *shell);
int						is_var_char(char c);

/* Heredock expansion */
void					expand_cmd_heredoc(char **cmd, t_shell *shell, int fd);

/* Expansion functions*/
char					*expand_cmd(char *token, t_shell *shell);
void					init_expand(t_exp *exp);
char					*get_env_value(t_list *env, char *key);
int						get_var_len(char *str, int start);
char					*extract_var_name(char *str, int start, int len);
void					expand_cmd_list(t_cmd *cmd_list, t_shell *shell);
int						calculate_expanded_length(char *str, t_shell *shell);
char					*expand_variables_in_token(char *token, t_shell *shell);
void					expand_cmd_array(char **cmd, t_shell *shell);
void					expand_redirection_list(t_redirec *redirec,
							t_shell *shell);
char					*get_expanded_value(char *var_name, t_shell *shell);
void					remove_quotes_from_cmd_array(char **cmd);
void					remove_quotes_from_redirection_list(t_redirec *redirec);
void					process_dollar_sign(char *token, t_exp *exp,
							t_shell *shell);
void					h_quotes(char c, t_exp *exp);

/* Redirection functions */
t_redirec				*create_redirec_node(char *name, t_type type);
void					add_redirec_node(t_redirec **head, t_redirec *new);
void					free_redirec_list(t_redirec *head);
void					print_redirec_list(t_redirec *head);
int						check_redirection_type(char **str, int i);
int						first_token_is_fully_quoted(char *cmd_str);
int						is_redir_char(char c);
t_redirec				*create_appropriate_redirection_node(char *filename,
							int redir_type);
int						add_redirections(char **tokens,
							t_redirec **redirec_list);
char					*parse_redirections(char *cmd_str,
							t_redirec **redirec_list);
int						process_special_cmd_cases(t_cmd *current,
							char *cmd_str);
int						setup_cmd_struct_with_redirection(t_cmd *current,
							char *cmd_str);
char					*remove_quotes(char *token);
char					**tokenize_with_redirections(char *cmd_str);
int						count_valid_tokens(char **tokens);
char					*build_cmd_string(char **tokens, int token_count);

/* Special split functions */
void					update_quotes_and_skip(t_split *split);
int						count_and_skip_delimiters(t_split *split);
char					*extract_single_token(char *str, int start, int end);
void					cleanup_tokens(char **tokens, int count);
char					**allocate_and_extract(t_split *split);
char					**quote_aware_split(char *str, char delimiter);
void					init_split(t_split *split, char *str, char delimiter);

/* Syntax Error functions */
int						handle_quotes(char *line);
int						redire_check(char *line);
int						handle_redir(char *line);
char					**tokenize_pipe(char *cmd_str);
int						handle_pipe(char *line);
int						syntax_error(char *line);

/* Helper functions from utils_a.c */
int						free_cmd_array(char **cmds);
int						allocate_token(t_cmd **token, char **cmds);
int						setup_cmd_struct(t_cmd *current, char *cmd_str);
int						create_next_node(t_cmd *current, int has_next);
t_cmd					*get_first_cmd(t_cmd *node);

/* Helper functions from utils_b.c */
int						arg_create(t_cmd *token, char **cmds);
t_cmd					*handle_token_error(char **cmds, t_cmd *token);
t_cmd					*tokenization(char *line);
void					print_cmd_list(t_cmd *token);
void					free_cmd_node(t_cmd *node);
void					free_cmd_list(t_cmd *token);

/* Helper functions from utils_c.c */
int						count_tokens_with_quotes(char *str, char delimiter);
int						skip_whitespace(char *str, int start);
int						is_whitespace(char c);
int						find_next_char_outside_quotes(char *str, char target,
							int start);

/*Quote removal after expansion */
void					remove_quotes_from_cmd_array(char **cmd);
void					remove_quotes_from_redirection_list(t_redirec *redirec);
int						is_inside_quotes(char *str, int pos);
char					**quote_aware_split(char *str, char delimiter);
char					*remove_quotes(char *token);
int						is_fully_quoted(char *str);
int						contains_only_quotes_and_spaces(char *cmd_str);

// void						set_signals_main(void);
// void						set_signals_child(void);
// int						exit_status(int val);
// int						control_g(bool option, bool value);

// EXECUTION

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif
//! ============================================================================
//! 							EXECUTION PHASE
//! ============================================================================
// t_list
char					**get_system_paths(t_list *v);
char					*get_executable_paths(char **path, char *cmd);
char					*get_next_line(int fd);
bool					process_heredocs(t_shell *val);
void					execute_commands(t_shell *val);
// redirections
bool					set_input(t_cmd *command, t_redirec *in);
bool					set_output(t_cmd *command, t_redirec *out);
bool					handle_redirections(t_cmd *command);
bool					setup_pipes(t_cmd *command);
bool					duplicate_standard_fds(t_cmd *cmd);
// unset
int						ft_unset(t_shell *val, char **cmd);
// std
bool					init_shell_fds(t_shell *shell);
void					cleanup_shell_fds(t_shell *shell);
bool					restore_standard_input(t_shell *shell);
// fork
void					child_process(t_shell *val, t_cmd *cmd);
void					parent_process(t_cmd *cmd);
void					execute_with_fork(t_shell *val);
// built_in
void					execute_builtin(char **cmd, t_shell *val);
int						is_builtin(char *cmd);
int						ft_exit(char **cmd, t_shell **shell);
//	//export
void					add_export_list(t_list **env, char *value, char *key,
							bool eg);
void					sort_export(t_list *var);
int						export_new(char *str, t_shell *var);
int						ft_export_variable(t_shell *var, char **cmd);
//	//export_utils
char					*get_valide_key(char *str);
t_list					*ft_copy_env(t_list *env);
void					swap_nodes(t_list *node1, t_list *node2);
void					desplay_list_export(t_list *list);
//	//cd
char					*resolve_cd_path(char *str, t_list *env);
void					update_env(char *key, char *value, t_list **env);
int						ft_cd(t_list *env, char *path);
char					*get_value(t_list *env, char *key);
//	//echo
int						ft_echo(char **cmd);
// error
void					error_message(int error_num, char *message);
void					errput(char *s);
// list_utils
int						list_size(t_list *list);
void					list_add_back(t_list **list, t_list *new);
t_list					*list_new_node(char *value, char *key, bool eg);
// environment_utils
void					add_default_env(t_list **list);
char					*add_shlvl(char *value);
char					**build_environment_array(t_list *list);
// environment
void					set_value_key(char *line, char **key, char **value);
t_list					*check_and_create_env_node(char *key, char *value);
t_list					*set_env(char **env);
t_list					*environment(char **env);
// leaks meme
void					free_list_node(t_list *node);
void					free_list(t_list **node);
void					cleanup_shell(t_shell **shell);
void					p2char(char ***ptr);
// leaks fd
void					clear_all_pipes(t_cmd *cmd);
void					close_fd(int *fd);
void					initialize_command_fds(t_cmd *cmd);
// signals
void					set_signals_child(void);
void					signal_herdoc(int sig);
void					set_signals_main(void);
// exit status
bool					wait_and_exit(int pid);
#endif