/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniheader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimoes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:52:42 by learodri          #+#    #+#             */
/*   Updated: 2023/09/01 04:47:34 by msimoes-         ###   ########.fr       */
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


typedef struct s_token
{
	char *token;
    struct s_token *next;
}t_token;


typedef struct s_shell
{
	char **env;
	char *input;
	char *path;
	int exit_s;
	int	nb_pipe;
	int	expand;
	t_token *head;
}t_shell;



//struct -- 

t_shell *shell(void);

//libft

int		ft_strlen(char *s);
char    *ft_strcpy(char *s1, char *s2);
char	*ft_strdup(char *s1);

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

#endif