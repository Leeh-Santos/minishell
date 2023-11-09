/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimoes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:15:04 by learodri@st       #+#    #+#             */
/*   Updated: 2023/11/08 02:39:01 by msimoes-         ###   ########.fr       */
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
void	fill_it(t_node *node, int fd)
{
	char	*buffer;
	char	*tmp;

	tmp = ft_strdup(node->arguments[0]);
	while (1)
	{
		buffer = readline("> ");
		if (buffer)
		{
			if (ft_strlen(buffer) == ft_strlen(tmp)
				&& !ft_strncmp(tmp, buffer, ft_strlen(node->arguments[0])))
				break ;
			escreve_it(fd, buffer);
		}
		else
			break ;
	}
	free (tmp);
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
