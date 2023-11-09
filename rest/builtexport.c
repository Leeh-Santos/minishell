/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtexport.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimoes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:24:49 by learodri@st       #+#    #+#             */
/*   Updated: 2023/11/07 21:31:50 by msimoes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniheader.h"

//line 26: traz env de volta porque se var for igual da free antes

void	insert_var(char **env, char *var)
{
	int		i;
	char	**copy_env;

	i = 0;
	if (exist_var(var, env))
	{
		delete_var(var, env);
		env = shell()->env;
	}
	while (env[i])
		i++;
	copy_env = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (env[i])
	{
		copy_env[i] = env[i];
		i++;
	}
	copy_env[i] = ft_strdup(var);
	copy_env[i + 1] = NULL;
	free(shell()->env);
	shell()->env = copy_env;
}

int	valid_var(char *var)
{
	int	i;

	i = 0;
	if (ft_isdigit(var[i]))
		return (0);
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_' && var[i] != '=')
			return (0);
		i++;
	}
	return (1);
}

void	print_export_line(char *env_line, int fd)
{
	int		i;

	i = 0;
	ft_putstr_fd("declare -x ", 1);
	while (env_line[i] != '\0' && env_line[i] != '=')
	{
		ft_putchar_fd(env_line[i], fd);
		i++;
	}
	if (env_line[i] == '=')
	{
		ft_putchar_fd(env_line[i], fd);
		ft_putchar_fd('\"', fd);
		i++;
		while (env_line[i] != '\0')
		{
			ft_putchar_fd(env_line[i], fd);
			i++;
		}
		ft_putchar_fd('\"', fd);
	}
	ft_putchar_fd('\n', fd);
}

//line 102: antes tava env no primeiro arg aqui
void	export_it(char **line, char **env, int fd)
{
	int	i;

	i = 0;
	if (!line[1])
	{
		while (env[i])
		{
			print_export_line(env[i], fd);
			i++;
		}
	}
	else
	{
		if (valid_var(line[1]))
			insert_var(env, line[1]);
		else
		{
			ft_putstr_fd("export: \'", fd);
			ft_putstr_fd(line[1], fd);
			ft_putstr_fd("\': not a valid identifier\n", fd);
		}
	}
}
