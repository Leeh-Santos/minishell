/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:59:22 by learodri          #+#    #+#             */
/*   Updated: 2023/09/21 16:48:06 by learodri@st      ###   ########.fr       */
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
		if (node->nodeType == E_APPEND || node->nodeType == E_HDOC)
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
	//sginal here?
	if (!check_ins(node)) //nao tem in? entao o in fdpipe vira       --tavez com next in aqui
	{
		dup2(shell()->in, STDIN_FILENO);
		close(shell()->in); //cuidado para nao fechar na primeira exec
	}
	else
		close(shell()->in); //se comenta ls vai 
	if (!check_outs(node)) // se nao tiver > >> node vai ter que cuspir no pipe
	{
		dup2(shell()->out, STDOUT_FILENO); //cospe neesse pipefd[1]
		close(shell()->out);
	}
	else //é porque ja tem out entao fechamos esse end pipefd[1]
		close(shell()->out);	
	
	for_ins(node, 0);
	for_outs(node, 0);
			
}