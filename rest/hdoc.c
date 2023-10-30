/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri <learodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:15:04 by learodri@st       #+#    #+#             */
/*   Updated: 2023/10/30 19:47:20 by learodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../miniheader.h"

void	escreve_it(int fd, char *buffer)
{
	char	*tmp;

	tmp = ft_strjoin(buffer, "\n"); //linha do input + /n
	write(fd, tmp, ft_strlen(tmp));
	free (buffer);
	free (tmp);
}

void	fill_it(t_node *node, int fd)
{
	char	*buffer;
	//char	*tmp;

	shell()->tmp = ft_strdup(node->arguments[0]);
	signal_in(SIGINT, sig_int2);
	while (1)
	{
		buffer = readline("> ");
		if (buffer)
		{
			if (ft_strlen(buffer) == ft_strlen(shell()->tmp)
				&& !ft_strncmp(shell()->tmp, buffer, ft_strlen(node->arguments[0])))
				break ;
			escreve_it(fd, buffer);
		}
		else
			break ;
	}
	free (shell()->tmp);
	free (buffer);
}

void    dale_hdoc(t_node *node)
{

	int	fd;
	//signal_in(SIGINT, SIG_DFL);
	//signal_in(SIGQUIT, SIG_DFL);
	fd = open(".h_doc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		redir_error(node);
	shell()->hdoc++;
	fill_it(node, fd); //faz o hdorc e joga no ficheiro
	close(fd); //fecha
	fd = open(".h_doc_tmp", O_RDONLY, 0644);
	if (fd == -1)
		redir_error(node);
	dup2(fd, STDIN_FILENO);
	unlink(".h_doc_tmp");
}
