/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_arvo2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimoes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 21:56:40 by msimoes-          #+#    #+#             */
/*   Updated: 2023/11/10 21:56:40 by msimoes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniheader.h"

t_token	*finish_initialization(t_token *start, t_node **new, int *nb_str)
{
	t_token	*tmp;

	tmp = start;
	*new = malloc(sizeof(t_node));
	if (!(*new) || !tmp)
		return (NULL);
	(*new)->nodeType = built_ou_cmd(tmp);
	(*new)->left = NULL;
	(*new)->right = NULL;
	(*new)->up = NULL;
	(*new)->pipe[0] = 0;
	(*new)->pipe[1] = 0;
	(*new)->arguments = malloc(sizeof(char *) * ((*nb_str) + 1));
	if (!(*new)->arguments)
	{
		free(*new);
		return (NULL);
	}
	return (tmp);
}

t_token	*initialize_for_cmd(t_token *start, t_node **new, int *nb_str)
{
	t_token	*tmp;

	tmp = start;
	*nb_str = 0;
	while (tmp)
	{
		if (tmp->type == -1)
			break ;
		if (tmp->type == 0)
			(*nb_str)++;
		tmp = tmp->next;
	}
	if (!(*nb_str))
		return (NULL);
	return (finish_initialization(start, new, nb_str));
}

void	populate_arguments(t_node *new, t_token *tmp, int *i)
{
	while (tmp)
	{
		if (tmp->type == -1)
		{
			new->arguments[*i] = NULL;
			send_to_tree(new);
			return ;
		}
		if (tmp->type == 0)
		{
			new->arguments[*i] = ft_strdup(tmp->token);
			(*i)++;
		}
		tmp = tmp->next;
	}
}

t_token	*for_cmd(t_token *start)
{
	t_token	*tmp;
	t_node	*new;
	int		nb_str;
	int		i;

	tmp = initialize_for_cmd(start, &new, &nb_str);
	if (!tmp)
		return (NULL);
	tmp = start;
	i = 0;
	populate_arguments(new, tmp, &i);
	new->arguments[i] = NULL;
	send_to_tree(new);
	return (NULL);
}
