/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri <learodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:59:22 by learodri          #+#    #+#             */
/*   Updated: 2023/09/19 20:26:13 by learodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../miniheader.h"

void	for_ins(t_node *node, int flag)
{
	int	fdin;
	
	while (node->left)
	{
		node = node->left;
		if (node->nodeType == E_IN || node->nodeType == E_HDOC)
		{
			if (!flag)
			{
				if (node->nodeType == E_IN)
				{
					fdin = open(node->arguments[0], O_RDONLY, 0644);
					if (fdin == -1)
						redir_error(node);
					dup2(fdin, STDIN_FILENO);
				}
				else
					printf("heredoc ainda nao");
					//fd = heredocshit
					// dupeia
				flag++;
			}
			else
				open_ins(node);
		}
	}
}

void	for_outs(t_node *node, int flag)
{
	int fd;
	
	while (node->left)
	{
		node = node->left;
		if (node->nodeType == E_OUT || node->nodeType == E_APPEND)
			{
				if (!flag)
				{
					if (node->nodeType == E_OUT)
						fd = open(node->arguments[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
					else
						fd = open(node->arguments[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
					if (fd == -1)
						redir_error(node);
					flag++;
					dup2(fd, STDOUT_FILENO);
				}
				else
					open_outs(node);
			}	
    }
}

void	dale_redir(t_node *node)
{
	//sginal here?
	for_ins(t_node *node, 0);
	for_outs(t_node *node, 0);
			
}