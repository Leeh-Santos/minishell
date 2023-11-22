/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimoes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 02:36:48 by msimoes-          #+#    #+#             */
/*   Updated: 2023/11/09 02:36:48 by msimoes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniheader.h"

int	count_quotes(char *str)
{
	int		i;
	int		j;
	char	c;

	i = -1;
	j = 0;
	c = 0;
	while (str[++i])
	{
		if ((str[i] == '\'' || str[i] == '\"'))
		{
			if (!c)
				c = str[i];
			else if (c == str[i])
			{
				c = 0;
				j++;
			}
		}
		if ((str[i] == '\'' && c == '\'') || (str[i] == '\"' && c == '\"'))
			j++;
	}
	return (j);
}

char	*quote_cleaner(char *str, char *ret)
{
	int		i;
	int		j;
	char	c;

	i = -1;
	j = 0;
	c = 0;
	while (str[++i])
	{
		if ((str[i] == '\'' || str[i] == '\"'))
		{
			if (!c)
				c = str[i];
			else if (c == str[i])
			{
				c = 0;
				continue ;
			}
		}
		if ((str[i] == '\'' && c == '\'') || (str[i] == '\"' && c == '\"'))
			continue ;
		ret[j++] = str[i];
	}
	ret[j] = 0;
	return (ret);
}

char	*del_quotes(char *str)
{
	int		delete;
	char	*ret;

	delete = count_quotes(str);
	if (delete == 0)
		return (str);
	ret = malloc(sizeof(char) * ((ft_strlen(str) - delete) + 1));
	if (!ret)
		return (0);
	ret = quote_cleaner(str, ret);
	free(str);
	return (ret);
}
