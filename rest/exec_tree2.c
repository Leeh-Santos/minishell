/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimoes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:30:51 by learodri          #+#    #+#             */
/*   Updated: 2023/11/09 02:30:09 by msimoes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniheader.h"

void	process_node(t_node *node, int *fd, int *flag)
{
	if (node->nodeType == E_IN || node->nodeType == E_HDOC)
		open_ins(node);
	if (node->nodeType == E_OUT || node->nodeType == E_APPEND)
	{
		if (!(*flag))
		{
			if (node->nodeType == E_OUT)
				*fd = open(node->arguments[0], O_CREAT | \
				O_WRONLY | O_TRUNC, 0644);
			else
				*fd = open(node->arguments[0], O_CREAT | \
				O_WRONLY | O_APPEND, 0644);
			if (*fd == -1)
				redir_error(node);
			(*flag)++;
		}
		else
			open_outs(node);
	}
}

void	simple_built(t_node *root)
{
	t_node	*node;
	int		fd;
	int		flag;

	node = root;
	fd = 1;
	flag = 0;
	while (node->left)
	{
		node = node->left;
		process_node(node, &fd, &flag);
	}
	which_builtin(root, fd);
}

void	papa_process(t_node *node)
{
	if (shell()->nb_cmd != 1)
	{
		if (shell()->in > 0)
			close(shell()->in);
		close(node->pipe[1]);
		shell()->in = node->pipe[0];
	}
	else
	{
		close(node->pipe[0]);
		close(node->pipe[1]);
		if (shell()->in > 0)
			close(shell()->in);
	}
}

void	pipe_it(t_node *sub, t_try *bora)
{
	if (pipe(sub->pipe) == -1)
	{
		ft_putstr_fd("Error: couldn't open pipe\n", STDERR_FILENO);
		shell()->exit_s = 1;
		exit(shell()->exit_s);
	}
	bora->pid = fork();
	if (bora->pid < 0)
	{
		ft_putstr_fd("Error: couldn't create a new process\n", STDERR_FILENO);
		shell()->exit_s = 1;
		exit(shell()->exit_s);
	}
	else if (bora->pid == 0)
		cmd_simplao(sub, 1, bora);
	papa_process(sub);
}
