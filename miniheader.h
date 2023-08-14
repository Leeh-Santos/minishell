/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniheader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:52:42 by learodri          #+#    #+#             */
/*   Updated: 2023/08/11 16:44:24 by learodri@st      ###   ########.fr       */
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
    struct t_token *next;
}t_token;


typedef struct s_shell
{
	char **env;
	char *input;
	char *path;
	int exit_s;
	int	nb_pipe;
	int	expand;
	struct t_token *head; // ou na uma global
}t_shell;



//struct -- 

t_shell *shell(void);

//libft

int	ft_strlen(char *s);
char    *ft_strcpy(char *s1, char *s2);
char	*ft_strdup(char *s1);

//signal
void	handle_sigint(int sig);

//errors
void	display_error(char *str, int x);

//input & parse

void	inputcheck(char *input);
void	quotecheck(char *input, int i, int flag);
void	forbidenchar(char *input);
void		verify_c(char c, int i, char *in);
void	redicheck(char *input, int i);

#endif