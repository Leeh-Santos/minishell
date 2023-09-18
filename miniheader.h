/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniheader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:52:42 by learodri          #+#    #+#             */
/*   Updated: 2023/09/18 15:08:53 by learodri@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
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
    int pid;
    int in;
    int out;
    int next_in;
	int	nb_pipe;
	int	expand;
	t_token *head;
	t_node *root;
}t_shell;



void	print_node_recebido(t_node *node);

//struct -- 

t_shell *shell(void);

//libft

int		ft_strlen(char *s);
char    *ft_strcpy(char *s1, char *s2);
char	*ft_strdup(char *s1);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);

void	ft_putendl_fd(char *s, int fd);

//signal
void	handle_sigint(int sig);

//errors
void	display_error(char *str, int x);

//input & parse

int 	char_checker(char c);
int 	skip_spaces(char c, int *i, char **in);
void	del_emptyQuotes(void);
void	inputcheck(char *input);
void	quotecheck(char *input, int i, int flag);
void	forbidenchar(char *input);
void	verify_c(char c, int i, char *in);
void	redicheck(char *input, int i);
void	token_it(char *in);
//free
void	free_linked(void);
void	free_na_tree(t_node *root);

//tree stuff
void	token_type(void);
void token_tree(t_token *head);
int	check_redir_node(t_node *node);
int	check_pipe_node(t_node *node);
int	check_cmd_node(t_node *node);
void	add_on_top(t_node *node);
void		where_redir(t_node *node);
void	where_cmd(t_node *node);

//exec tree

void	exec_tree(void);

#endif