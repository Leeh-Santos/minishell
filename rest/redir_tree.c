/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:59:22 by learodri          #+#    #+#             */
/*   Updated: 2023/09/25 16:05:05 by learodri@st      ###   ########.fr       */
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
					{
						fd = open(node->arguments[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
						printf("fd é desse node %s\n", node->arguments[0]);
					}
					else
						fd = open(node->arguments[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
					if (fd == -1)
						redir_error(node);
					flag++;
					printf("trava aqui\n"); 
					if (dup2(fd, 1) == - 1){
						printf("pau no dup\n");
					} //aqui pohaa, asda >a s
					printf("nao fica infinito\n");
					close(fd);
				}
				else
					open_outs(node);
			}	
    }
}

int		check_outs(t_node *node)
{
	while (node->left)
	{
		node = node->left;
		if (node->nodeType == E_OUT || node->nodeType == E_APPEND)
			return (1);
	}
	return (0);
}

int		check_ins(t_node *node)
{
	while (node->left)
	{
		node = node->left;
		if (node->nodeType == E_IN || node->nodeType == E_HDOC)
			return (1);
	}
	return (0);
}

void	dale_redir(t_node *node)  //redir2 somente com esses dois ifs deve dar
{
	for_ins(node, 0);
	for_outs(node, 0);			
}

void	dale_redir2(t_node *node)  //redir2 somente com esses dois ifs deve dar
{
	if (check_ins(node))
	{
		if (shell()->in)
			close(shell()->in);
		for_ins(node, 0);
	}
	else
		dup2(shell()->in, 0);
	if (check_outs(node))
	{
		close(node->pipe[1]);
		for_outs(node, 0);
	}
	else
	{
		if (shell()->nb_cmd > 1)
		{
			dup2(node->pipe[1], 1);
			close(node->pipe[1]);
		}
		else
			close(node->pipe[1]);
	}
	
	
	
			
}