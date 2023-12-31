/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimoes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:04:36 by learodri@st       #+#    #+#             */
/*   Updated: 2023/09/11 04:36:35 by msimoes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../miniheader.h"


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
	printf("nodetipo - %d , left \n", new_node->nodeType);
}

void	add_on_right(t_node *node, t_node *new_node)
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
	printf("nodetipo - %d , right \n", new_node->nodeType);
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
	printf("nodetipo - %d , on top \n", node->nodeType);
}

void		where_redir(t_node *node)
{
	t_node	*first;
	t_node	*next;	

	if (!node)
		return ;
	first = shell()->root;
	if (!first) // se avore null redir vai pra cima
		add_on_top(node);
	else if (check_cmd_node(first) || check_redir_node(first)) // se o tree for cmd ou outro redir, vai pra esquerda
		add_on_left(first, node);
	else if (check_pipe_node(first)) // se tamo num pipe
	{
		next = first->right; // mira no right kid
		if (!next || check_redir_node(next))// se nao tem kid a direita do pipe ou for redir tambem, vai para direta
			add_on_right(first, node);
		else
			add_on_left(next, node); // redir na esquerda
	}
}

void	where_cmd(t_node *node)
{
	t_node	*first;

	first = shell()->root;
	if (!first || check_redir_node(first))
		add_on_top(node); // vai pra cima se ligando com a esquerda do parent
	else if (check_pipe_node(first)) // se for pipe vai pa direita
		add_on_right(first, node);
}
