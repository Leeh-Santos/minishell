/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimoes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:36:54 by learodri@st       #+#    #+#             */
/*   Updated: 2023/11/09 00:07:01 by msimoes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniheader.h"

void	pwd_func(int fd)
{
	char	*path;

	path = getcwd(NULL, 1025);
	if (path == NULL)
	{
		ft_putstr_fd("Error: ", fd);
		ft_putstr_fd(strerror(errno), fd);
		ft_putchar_fd('\n', fd);
		free(path);
	}
	else
	{
		ft_putstr_fd(path, fd);
		ft_putchar_fd('\n', fd);
	}
	free(path);
}

int	var_ok(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	env_print(char **env, int fd)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (var_ok(env[i]))
		{
			ft_putstr_fd(env[i], fd);
			ft_putchar_fd('\n', fd);
		}
		i++;
	}
}
