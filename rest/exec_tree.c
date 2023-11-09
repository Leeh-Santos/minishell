/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimoes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:30:51 by learodri          #+#    #+#             */
/*   Updated: 2023/11/09 03:18:34 by msimoes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniheader.h"

void	wtf_hdoc(t_node *node)
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
			free (buffer);
		}
		else
			break ;
	}
	free (tmp);
	free (buffer);
}

void	redir_error(t_node *node)
{
	ft_putstr_fd("Error: couldn't open file: ", 2);
	ft_putstr_fd(node->arguments[0], 2);
	ft_putstr_fd("\n", 2);
	shell()->exit_s = 1;
	exit(shell()->exit_s);
}

void	open_ins(t_node *node)
{
	if (node->nodeType == E_IN)
	{
		if (open(node->arguments[0], O_RDONLY, 0644) == -1)
			redir_error(node);
	}
	else
		wtf_hdoc(node);
}

void	open_outs(t_node *node)
{
	t_node	*tmp;
	int		fd_tmp;

	tmp = node;
	fd_tmp = open(node->arguments[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_tmp == -1)
		redir_error(tmp);
	close (fd_tmp);
}

void	which_builtin(t_node *node, int fd)
{
	if (!ft_strncmp(node->arguments[0], "echo", 5))
		echo_func(node, fd);
	else if (!ft_strncmp(node->arguments[0], "pwd", 4))
		pwd_func(fd);
	else if (!ft_strncmp(node->arguments[0], "cd", 3))
		cd_func(node->arguments, shell()->env);
	else if (!ft_strncmp(node->arguments[0], "env", 4))
		env_print(shell()->env, fd);
	else if (!ft_strncmp(node->arguments[0], "exit", 5))
		exit_it(node->arguments, shell()->env);
	else if (!ft_strncmp(node->arguments[0], "export", 7))
		export_it(node->arguments, shell()->env, fd);
	else if (!ft_strncmp(node->arguments[0], "unset", 6))
		unset_it(node->arguments, shell()->env);
}
