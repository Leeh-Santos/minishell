/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tree_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimoes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:13:42 by msimoes-          #+#    #+#             */
/*   Updated: 2023/11/09 20:13:42 by msimoes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniheader.h"

//redir2 somente com esses dois ifs deve dar
void	dale_redir(t_node *node)
{
	for_ins(node, 0);
	for_outs(node, 0);
}

//redir2 somente com esses dois ifs deve dar
void	dale_redir2(t_node *node, t_try *bora)
{
	(void)bora;
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
