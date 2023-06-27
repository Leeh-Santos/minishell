/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniheader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri <learodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:52:42 by learodri          #+#    #+#             */
/*   Updated: 2023/06/27 19:07:39 by learodri         ###   ########.fr       */
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
	
}t_shell;

//struct

t_shell *shell(void);

//libft

int	ft_strlen(char *s);
char    *ft_strcpy(char *s1, char *s2);
char	*ft_strdup(char *s1);

//signal
void	handle_sigint(int sig);

//errors
void	display_error(char *str, int x);

//input

void	inputcheck(char *input);
void	quotecheck(char *input, int i);

#endif