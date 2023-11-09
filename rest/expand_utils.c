/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimoes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:28:19 by msimoes-          #+#    #+#             */
/*   Updated: 2023/09/10 19:28:19 by msimoes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniheader.h"

int	expander_len(char *str)
{
	int	i;
	int	len;

	len = 0;
	i = -1;
	if (!str)
		return (0);
	while (str[++i] && str[i] != '$')
		len++;
	while (str[i] && (str[i] != ' ' && str[i] != '\t' \
	&& str[i] != '"' && str[i] != '\'' && str[i] != '$'))
		i++;
	while (str[i++])
		len++;
	return (len);
}

int	verify_var(char *str, char *env)
{
	int	i;

	i = -1;
	while (str[++i] && env[i] != '=' && str[i] == env[i])
		;
	return (!str[i] && env[i] == '=');
}

int	env_char(char c)
{
	if ((c >= '0' && c <= '9' ) || (c >= 'A' && c <= 'Z') || \
	(c >= 'a' && c <= 'z') || c == '_' || c == '?')
		return (1);
	return (0);
}
