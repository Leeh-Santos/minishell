/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:04:36 by learodri@st       #+#    #+#             */
/*   Updated: 2023/11/16 16:34:12 by learodri@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniheader.h"

void	add_on_left(t_node *current, t_node *new_node)
{
	if (!current || !new_node)
		return ;
	if (current->left)
	{
		new_node->left = current->left;
		current->left->up = new_node;
	}
	current->left = new_node;
	new_node->up = current;
}

// line 34 : se ja tem node faz relacao pai e filho
// jogando node anterior para a esquerda
void	add_on_right(t_node *node, t_node *new_node)
{
	if (!node || !new_node)
		return ;
	if (node->right)
	{
		new_node->left = node->right;
		node->right->up = new_node;
	}
	node->right = new_node;
	new_node->up = node;
}

void	add_on_top(t_node *node)
{
	t_node	*first;

	first = shell()->root;
	if (!first)
		first = node;
	else
	{
		node->left = first;
		first->up = node;
		first = node;
	}
	shell()->root = first;
}

//printf("nodetipo - %d , on top \n", node->nodetype);
//line 76 : se avore null redir vai pra cima
//line 78 : se o tree for cmd ou outro redir, vai pra esquerda
//line 80 : se tamo num pipe
//line 82 : mira no right kid
//line 83 : se nao tem kid a direita do pipe ou
//for redir tambem, vai para direta
//line 86 : redir na esquerda
void	where_redir(t_node *node)
{
	t_node	*first;
	t_node	*next;	

	if (!node)
		return ;
	first = shell()->root;
	if (!first)
		add_on_top(node);
	else if (check_cmd_node(first) || check_redir_node(first))
		add_on_left(first, node);
	else if (check_pipe_node(first))
	{
		next = first->right;
		if (!next || check_redir_node(next))
			add_on_right(first, node);
		else
			add_on_left(next, node);
	}
}

//line 98 : vai pra cima se ligando com a esquerda do parent
//line 99 : se for pipe vai pa direita
void	where_cmd(t_node *node)
{
	t_node	*first;

	first = shell()->root;
	if (!first || check_redir_node(first))
		add_on_top(node);
	else if (check_pipe_node(first))
		add_on_right(first, node);
}
