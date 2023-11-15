/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_aspas.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimoes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 07:39:54 by msimoes-          #+#    #+#             */
/*   Updated: 2023/11/11 07:39:54 by msimoes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniheader.h"

int	is_redir_pipe(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

void	continue_str(char *in, char *tmp, int *i, t_params *p)
{
	(*i)++;
	while (in[*i] && (in[*i] >= 32 && in[*i] <= 126))
	{
		if (in[*i] == 39 || in[*i] == '"')
			p->quote++;
		if (p->quote % 2 == 0 && (in[*i] == ' ' || \
		in[*i] == '\t' || is_redir_pipe(in[*i])))
			break ;
		tmp[p->k] = in[*i];
		(*i)++;
		p->k++;
	}
	tmp[p->k] = '\0';
	return ;
}

int	end_aspas(char *in, char *tmp, int *i, t_params *p)
{
	tmp[p->k++] = p->c;
	if (in[*i + 1] == ' ' || in[*i + 1] == '\t' || \
	in[*i + 1] == '\0' || is_redir_pipe(in[*i + 1]))
	{
		tmp[p->k] = '\0';
		(*i)++;
		return (0);
	}
	else
		continue_str(in, tmp, i, p);
	return (0);
}

void	aspasword(char *in, char *tmp, int *i)
{
	t_params	p;

	p.k = 0;
	p.flag = 0;
	p.quote = 0;
	p.c = in[*i];
	while (in[*i])
	{
		if (in[*i] == p.c && p.flag)
		{
			p.flag = end_aspas(in, tmp, i, &p);
			return ;
		}
		p.flag = 1;
		tmp[p.k] = in[*i];
		(*i)++;
		p.k++;
	}
}

void	update_quote(void)
{
	t_token	*tmp;

	tmp = shell()->head;
	if (!tmp)
		return ;
	while (tmp)
	{
		tmp->token = del_quotes(tmp->token);
		tmp = tmp->next;
	}
}
