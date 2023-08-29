/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniheader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri <learodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:52:42 by learodri          #+#    #+#             */
/*   Updated: 2023/08/29 17:49:35 by learodri         ###   ########.fr       */
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
    struct Node* up;    
    struct Node* left;
    struct Node* right;
}t_node;


typedef struct s_shell
{
	char **env;
	char *input;
	char *path;
	int exit_s;
	int	nb_pipe;
	int	expand;
	t_token *head;
	t_node *root;
}t_shell;



//struct -- 

t_shell *shell(void);

//libft

int		ft_strlen(char *s);
char    *ft_strcpy(char *s1, char *s2);
char	*ft_strdup(char *s1);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

//signal
void	handle_sigint(int sig);

//errors
void	display_error(char *str, int x);

//input & parse

void	inputcheck(char *input);
void	quotecheck(char *input, int i, int flag);
void	forbidenchar(char *input);
void	verify_c(char c, int i, char *in);
void	redicheck(char *input, int i);
void	token_it(char *in);
//free
void	free_linked(void);

//tree
void	token_type(void);
t_node *token_tree(t_token *head);

#endif