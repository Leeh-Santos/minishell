/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimoes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:15:04 by learodri@st       #+#    #+#             */
/*   Updated: 2023/11/10 21:08:07 by msimoes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniheader.h"

//line 20: linha do input + /n
void	escreve_it(int fd, char *buffer)
{
	char	*tmp;

	tmp = ft_strjoin(buffer, "\n");
	write(fd, tmp, ft_strlen(tmp));
	free (buffer);
	free (tmp);
}

//line 41: escreve no file
void	sig_int2(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_redisplay();
		if (shell()->root)
			free_na_tree(shell()->root);
		if (shell()->head)
			free_linked();
		if (shell()->env)
			free_no_env();
		if (shell()->path1)
			free(shell()->path1);
		if (shell()->tmp)
			free(shell()->tmp);
		shell()->exit_s = 130;
		exit(shell()->exit_s);
	}
}

void	fill_it(t_node *node, int fd)
{
	char	*buffer;

	shell()->tmp = ft_strdup(node->arguments[0]);
	signal_in(SIGINT, sig_int2);
	while (1)
	{
		buffer = readline("> ");
		if (buffer)
		{
			if (ft_strlen(buffer) == ft_strlen(shell()->tmp)
				&& !ft_strncmp(shell()->tmp, buffer, \
				ft_strlen(node->arguments[0])))
				break ;
			escreve_it(fd, buffer);
		}
		else
			break ;
	}
	free (shell()->tmp);
	free (buffer);
}

//line 56: signal
//line 61:faz o hdorc e joga no ficheiro
//line 62: fecha
void	dale_hdoc(t_node *node)
{
	int	fd;

	fd = open(".h_doc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		redir_error(node);
	shell()->hdoc++;
	fill_it(node, fd);
	close(fd);
	fd = open(".h_doc_tmp", O_RDONLY, 0644);
	if (fd == -1)
		redir_error(node);
	dup2(fd, STDIN_FILENO);
	unlink(".h_doc_tmp");
}
