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

char	*del_quotes(char *str)
{
	int		i;
	int		j;
	char	*ret;

	i = -1;
	j = 0;
	while (str[++i])
		if (str[i] == '\'' || str[i] == '\"')
			j++;
	if (j == 0)
		return (str);
	ret = malloc(sizeof(char) * ((ft_strlen(str) - j) + 1));
	if (!ret)
		return (0);
	i = -1;
	j = -1;
	while (str[++i])
	{
		if (str[i] != '\'' && str[i] != '\"')
			ret[++j] = str[i];
	}
	ret[++j] = 0;
	free(str);
	return (ret);
}
