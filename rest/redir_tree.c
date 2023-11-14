/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:59:22 by learodri          #+#    #+#             */
/*   Updated: 2023/11/14 14:33:24 by learodri@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniheader.h"

void	for_ins(t_node *node, int flag)
{
	int	fdin;

	while (node->left)
	{
		node = node->left;
		if (node->nodetype == E_IN || node->nodetype == E_HDOC)
		{
			if (!flag)
			{
				if (node->nodetype == E_IN)
				{
					fdin = open(node->arguments[0], O_RDONLY, 0644);
					if (fdin == -1)
						redir_error(node);
					dup2(fdin, STDIN_FILENO);
				}
				else
					dale_hdoc(node);
				flag++;
			}
			else
				open_ins(node);
		}
	}
}

void	open_out_file(const char *file, int append, t_node *node)
{
	int	fd;

	if (append)
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		redir_error(node);
	else
	{
		if (dup2(fd, 1) == -1)
			ft_putendl_fd("not able to dup2 bro", 2);
		close(fd);
	}
}

void	for_outs(t_node *node, int flag)
{
	while (node->left)
	{
		node = node->left;
		if (node->nodetype == E_OUT || node->nodetype == E_APPEND)
		{
			if (!flag)
			{
				open_out_file(node->arguments[0], \
				node->nodetype == E_APPEND, node);
				flag++;
			}
			else
				open_outs(node);
		}
	}
}

int	check_outs(t_node *node)
{
	while (node->left)
	{
		node = node->left;
		if (node->nodetype == E_OUT || node->nodetype == E_APPEND)
			return (1);
	}
	return (0);
}

int	check_ins(t_node *node)
{
	while (node->left)
	{
		node = node->left;
		if (node->nodetype == E_IN || node->nodetype == E_HDOC)
			return (1);
	}
	return (0);
}
