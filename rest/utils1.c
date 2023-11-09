/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                            :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: msimoes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 02:36:29 by msimoes-          #+#    #+#             */
/*   Updated: 2023/11/09 02:36:29 by msimoes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniheader.h"

int	char_checker(char c)
{
	if (c == '\0' || c == '\n' || c == '|' || c == '<' || \
	c == '>' || c == ';' || c == '(' || c == ')')
		return (1);
	return (0);
}

int	skip_spaces(char c, int *i, char **in)
{
	int	flag;

	flag = 0;
	while (((*in)[*i]) && ((*in)[*i] == '\t' || (*in)[*i] == ' '))
	{
		if ((c == '>' || c == '<') && ((*in)[*i] == '\t' || (*in)[*i] == ' '))
			flag++;
		(*i)++;
	}
	return (flag);
}

static void	remove_token(t_token **prev, t_token **tmp)
{
	(*prev)->next = (*tmp)->next;
	free((*tmp)->token);
	free(*tmp);
	*tmp = (*prev)->next;
}

static void	process_tokens(t_token **tmp, t_token **prev)
{
	if (((*tmp)->token[0] == '"' && (*tmp)->token[1] == '"' && \
	(*tmp)->token[2] == '\0') || ((*tmp)->token[0] == 39 && \
	(*tmp)->token[1] == 39 && (*tmp)->token[2] == '\0') || \
	((*tmp)->token[0] == '\0'))
	{
		if (*prev)
			remove_token(prev, tmp);
		else
		{
			shell()->head = (*tmp)->next;
			free((*tmp)->token);
			free(*tmp);
			*tmp = shell()->head;
		}
	}
	else
	{
		*prev = *tmp;
		*tmp = (*tmp)->next;
	}
}

void	del_emptyquotes(void)
{
	t_token	*tmp;
	t_token	*prev;

	tmp = shell()->head;
	prev = NULL;
	while (tmp)
		process_tokens(&tmp, &prev);
}
