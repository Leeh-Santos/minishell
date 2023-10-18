/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniheader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri <learodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:52:42 by learodri          #+#    #+#             */
/*   Updated: 2023/10/18 21:06:37 by learodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>


typedef enum e_type
{
    E_CMD,
    E_PIPE,
    E_IN,
    E_OUT,
    E_APPEND,
    E_HDOC,
    E_BUILT
} t_type;


typedef struct s_token
{
	char *token;
    int type;
    struct s_token *next;
}t_token;

typedef struct s_node {
    int nodeType;
    char** arguments;
    int pipe[2];
    struct s_node *up;    
    struct s_node *left;
    struct s_node *right;
}t_node;


typedef struct s_shell
{
	char **env;
	char *input;
	char *path;
	int exit_s;
    int	kid_stats;
    int	nb_cmd_wait;
    int in;
    int hdoc;
    int next_in;
	int	nb_cmd;
	int	expand;
	t_token *head;
	t_node *root;
}t_shell;

typedef struct s_try
{
	int pid;
	int ffd;
}t_try;



void	print_node_recebido(t_node *node);

//struct -- 

t_shell *shell(void);

//libft

int		ft_strlen(char *s);
char    *ft_strcpy(char *s1, char *s2);
char	*ft_strdup(char *s1);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char    *ft_itoa(int n);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
char	**ft_split(const char *s, char c);
void	ft_putendl_fd(char *s, int fd);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memset(void *b, int c, size_t len);
int		ft_isascii(int a);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
int		ft_isalnum(int c);
//signal
void	handle_sigint(int sig);

//errors
void	display_error(char *str, int x);
void	rlp_error_msg(char *cmd);


//input & parse

int 	char_checker(char c);
int 	skip_spaces(char c, int *i, char **in);
void	del_emptyQuotes(void);
int 	inputcheck(char *input);
int 	quotecheck(char *input, int i, int flag);
int 	forbidenchar(char *input);
int 	verify_c(char c, int i, char *in);
int 	redicheck(char *input, int i);
void	token_it(char *in);

//expand
int	    expander_len(char *str);
int	    verify_var(char *str, char *env);
int	    env_char(char c);
char	*expand_check(char *input, char **env);

//free
void	free_linked(void);
void	free_na_tree(t_node *root);
void	free_split(char **args);
void	free_no_env(void);

//tree stuff
void	token_type(void);
void token_tree(t_token *head);
int	check_redir_node(t_node *node);
int	check_pipe_node(t_node *node);
int	check_cmd_node(t_node *node);
void	add_on_top(t_node *node);
void		where_redir(t_node *node);
void	where_cmd(t_node *node);
void	cmd_simplao(t_node *node, int key, t_try *bora);

//exec tree

void	exec_tree(void);

//path shit

char	*absolute_path(char *cmd);
int	is_path(char *str, char *path);
char	*search_rpath(char *cmd);
char	*getpath(char *cmd);

//redir

void	open_outs(t_node *node);
void	redir_error(t_node *node);
void	open_ins(t_node *node);
void	dale_redir(t_node *node);
void	dale_redir2(t_node *node, t_try *bora);
void    dale_hdoc(t_node *node);

//builts

void	echo_func(t_node *branch, int fd);
void	pwd_func(int fd);
void	env_print(char **env, int fd);
void	cd_func(char **line, char **env);
void	export_it(char **line, char **env, int fd);
void	unset_it(char **line, char **env);
void	exit_it(char **line, char **env);
void	delete_var(char *var, char **env);
int	exist_var(char *var, char **env);

//signal

void	signal_in(int sig, void (*func)());
void	sig_int(int signal);

#endif