/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_delword.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimoes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 07:40:15 by msimoes-          #+#    #+#             */
/*   Updated: 2023/11/11 07:40:15 by msimoes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniheader.h"

void	handle_pipe(char *tmp, int *i)
{
	tmp[0] = '|';
	tmp[1] = '\0';
	(*i)++;
}

void	handle_double_greater_than(char *tmp, int *i)
{
	tmp[0] = '>';
	tmp[1] = '>';
	tmp[2] = '\0';
	(*i) += 2;
}

void	handle_single(char c, char *tmp, int *i)
{
	tmp[0] = c;
	tmp[1] = '\0';
	(*i)++;
}

void	handle_double_less_than(char *tmp, int *i)
{
	tmp[0] = '<';
	tmp[1] = '<';
	tmp[2] = '\0';
	(*i) += 2;
}

void	delword(char c, char *in, char *tmp, int *i)
{
	if (c == '|')
		handle_pipe(tmp, i);
	else if (c == '>')
	{
		if (in[*i + 1] == '>')
			handle_double_greater_than(tmp, i);
		else
			handle_single(c, tmp, i);
	}
	else if (c == '<')
	{
		if (in[*i + 1] == '<')
			handle_double_less_than(tmp, i);
		else
			handle_single(c, tmp, i);
	}
}
