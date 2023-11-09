/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputcheck_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimoes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 02:56:31 by msimoes-          #+#    #+#             */
/*   Updated: 2023/11/09 02:56:31 by msimoes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniheader.h"

int	forbidenchar(char *input)
{
	int		i;
	char	c;

	i = 0;
	while (input[i])
	{
		if (input[i] == 39 || input[i] == '"')
		{
			c = input[i];
			if (input[i])
				i++;
			while (input[i] && input[i] != c)
				i++;
		}
		if (input[i] == ';' || input[i] == '\\' || input[i] == '[' || \
		input[i] == ']' || input[i] == '{' || input[i] == '}' || \
		input[i] == '(' || input[i] == ')')
			return (1);
		if (input[i])
			i++;
	}
	return (0);
}

int	quotecheck(char *input, int i, int flag)
{
	char	quote;

	while (input[i])
	{
		if (input[i] == 39 || input[i] == '"')
		{
			quote = input[i];
			flag = 1;
			i++;
			while (input[i])
			{
				if (input[i] == quote)
				{
					flag = 0;
					break ;
				}
				i++;
			}
		}
		if (input[i])
			i++;
	}
	if (flag)
		return (1);
	return (0);
}
