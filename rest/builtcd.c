/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtcd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimoes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:53:50 by learodri@st       #+#    #+#             */
/*   Updated: 2023/11/07 21:27:00 by msimoes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniheader.h"

void	create_old(char **env, char *old_path)
{
	int		i;
	char	**copy_env;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], "OLDPWD=", 7))
			return ;
	copy_env = malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (env[++i])
		copy_env[i] = env[i];
	copy_env[i] = ft_strjoin("OLDPWD=", old_path);
	copy_env[i + 1] = NULL;
	free(old_path);
	free(shell()->env);
	shell()->env = copy_env;
}

void	update_env(char *old_path, char *new_path, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
		{
			if (env[i])
				free(env[i]);
			env[i] = ft_strjoin("OLDPWD=", old_path);
		}
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			if (env[i])
				free(env[i]);
			env[i] = ft_strjoin("PWD=", new_path);
			if (new_path)
				free(new_path);
		}
		i++;
	}
}

void	error_cd(char *token)
{
	ft_putstr_fd("cd: ", 1);
	ft_putstr_fd(token, 1);
	ft_putstr_fd(": ", 1);
	ft_putstr_fd(strerror(errno), 1);
	ft_putchar_fd('\n', 1);
}

char	*go_home(char **env)
{
	int		i;
	int		j;
	int		n;
	char	*home;

	i = 0;
	n = 0;
	home = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
		{
			j = 5;
			home = malloc(sizeof(char) * ft_strlen(env[i]));
			while (env[i][j + n] != '\0')
			{
				home[n] = env[i][j + n];
				n++;
			}
			home[n] = '\0';
			return (home);
		}
		i++;
	}
	return (home);
}

void	cd_func(char **line, char **env)
{
	char	*new_path;
	char	*old_path;
	char	*home_path;

	old_path = getcwd(NULL, 1025);
	home_path = go_home(env);
	if (!line[1])
		chdir(home_path);
	else if (chdir(line[1]) == -1)
	{
		error_cd(line[1]);
		free(old_path);
		free(home_path);
		return ;
	}
	new_path = getcwd(NULL, 1025);
	update_env(old_path, new_path, env);
	create_old(env, old_path);
	free(home_path);
	free(old_path);
}
