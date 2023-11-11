/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_arvo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimoes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 18:50:55 by learodri          #+#    #+#             */
/*   Updated: 2023/11/10 21:57:30 by msimoes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniheader.h"
/*
void	print_node_recebido(t_node *node)
{
	t_node	*tmp = node;

	int i;

	i = 0;
	if (node->nodeType >= E_IN && node->nodeType <= E_HDOC)
		printf("nodetype %d - #0 %s - #1 %s\n", \
		tmp->nodeType, tmp->arguments[0], tmp->arguments[1]);
	else if (node->nodeType == E_PIPE)
		printf("PIPE CARAI \n");
	else if (node->nodeType == E_CMD || node->nodeType == E_BUILT)
	{
		printf("nodetype %d", tmp->nodeType);
		while (node->arguments[i])
		{
			printf(" - #%d %s",i , tmp->arguments[i]);
			i++;
		}
		printf("\n");
		
	}
		
}
*/

static int	redir_tipo(t_token *redir)
{
	t_token	*tmp;

	tmp = redir;
	if (tmp->token[0] == '<' && tmp->token[1] == '<')
		return (E_HDOC);
	else if (tmp->token[0] == '>' && tmp->token[1] == '>')
		return (E_APPEND);
	else if (tmp->token[0] == '<' && !tmp->token[1])
		return (E_IN);
	else if (tmp->token[0] == '>' && !tmp->token[1])
		return (E_OUT);
	else
		return (-1);
}

t_node	*redir_node(t_token *token_node, char *arg)
{
	t_token	*tmp;
	t_node	*new;

	tmp = token_node;
	new = malloc(sizeof(t_node));
	new->nodeType = redir_tipo(tmp);
	new->arguments = malloc(sizeof(char *) * 2);
	if (!new->arguments || !new)
		display_error("falha no malloc tree node", 0);
	new->arguments[0] = ft_strdup(arg);
	new->arguments[1] = NULL;
	new->left = NULL;
	new->right = NULL;
	new->up = NULL;
	new->pipe[0] = 0;
	new->pipe[1] = 0;
	return (new);
}

// ja manda o tipo do redir, o parsing que q ta ok! se nao da ruim
// line 199 : antes tava tmp == '|'
// line 204 : > arg
void	for_redir(t_token *start)
{
	t_token	*tmp;

	tmp = start;
	while (tmp)
	{
		if (tmp->type == -1)
			return ;
		if (tmp->type == 1)
		{
			send_to_tree(redir_node(tmp, tmp->next->token));
			tmp = tmp->next->next;
			continue ;
		}
		tmp = tmp->next;
	}
}

t_node	*pipe_node(void)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		display_error("deu ruim pipemalloc", 0);
	new->nodeType = E_PIPE;
	new->arguments = NULL;
	new->left = NULL;
	new->right = NULL;
	new->up = NULL;
	return (new);
}

//antes que eu esqueca, essa poha vai criando
//line 136 : echo >as asd asd
void	token_tree(t_token *head)
{
	t_token	*tmp;
	t_token	*pipe;

	pipe = NULL;
	tmp = head;
	if (!tmp)
		return ;
	pipe = for_cmd(tmp);
	for_redir(tmp);
	if (pipe)
	{
		send_to_tree(pipe_node());
		token_tree(pipe->next);
	}
}
