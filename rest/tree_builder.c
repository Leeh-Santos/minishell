/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:04:36 by learodri@st       #+#    #+#             */
/*   Updated: 2023/09/04 17:00:51 by learodri@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../miniheader.h"

void		where_redir(t_node *node)
{
	t_node	*first;
	t_node	*next;	

	if (!node)
		return ;
	first = shell()->root;
	if (!first) // se avore null redir vai pra cima
		add_on_top(node);
	else if (is_node_cmd(first) || is_node_red(first)) // se o tree for cmd ou outro redir, vai pra esquerda
		add_node_on_left(first, node);
	else if (is_node_pipe(first)) // se tamo num pipe
	{
		next = first->right; // mira no right kid
		if (!next || is_node_red(next))// se nao tem kid a direita do pipe ou for redir tambem, vai para direta
			add_node_on_right(first, node);
		else
			add_node_on_left(next, node); // redir na esquerda
	}
}

void	where_cmd(t_node *node)
{
	t_node	*first;

	first = shell()->root;
	if (!first || is_node_red(first))
		add_node_on_top(node); // vai pra cima se ligando com a esquerda do parent
	else if (is_node_pipe(first)) // se for pipe vai pa direita
		add_node_on_right(first, node);
}

void	add_node_on_left(t_node *current, t_node *new_node)
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

void	add_node_on_right(t_node *node, t_node *new_node)
{
	if (!node || !new_node)
		return ;
	if (node->right) // se ja tem node faz relacao pai e filho, jogando node anterior para a esquerda
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