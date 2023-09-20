/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:59:22 by learodri          #+#    #+#             */
/*   Updated: 2023/09/20 21:34:40 by learodri@st      ###   ########.fr       */
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

void	dale_redir(t_node *node)  //redir2 somente com esses dois ifs deve dar
{
	//sginal here?
	
	if (!check_out()) // se nao tiver > >> node vai ter que cuspir no pipe
	{
		dup2(shellout, finenoout); //cospe neesse pipefd[1]
		close(shelout);
	}
	else //é porque ja tem out entao fechamos esse end pipefd[1]
		close(shell_out);
		
	if (!check_in) //nao tem in? entao o in fdpipe vira       --tavez com next in aqui
	{
		dup2(shellin, filein)
		close(shellin); //cuidado para nao fechar na primeira exec
	}
	else
		close(shell.in);

	for_ins(node, 0);
	for_outs(node, 0);
			
}