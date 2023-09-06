/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri <learodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:30:51 by learodri          #+#    #+#             */
/*   Updated: 2023/09/06 21:45:24 by learodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../miniheader.h"

/*void	wtf_hdoc(t_node *node)
{

}

void	simple_built(t_node *root)
{
	
}

void	exec_tree(void)
{
	t_node	*root;

	
	root = shell()->root;
	if (!root)
		return ;
	
	if (!root.up && root.nodeType == E_HDOC)
		return (wtf_hdoc(root));
	if (!root.up && root.nodeType == E_BUILT)
		return (simple_built(root))
}