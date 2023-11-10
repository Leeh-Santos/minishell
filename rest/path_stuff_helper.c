/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_stuff_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimoes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 21:09:35 by msimoes-          #+#    #+#             */
/*   Updated: 2023/11/10 21:09:35 by msimoes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniheader.h"

char	**grab_paths(char **envp)
{
	char	**paths;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 4))
		{
			flag++;
			break ;
		}
		i++;
	}
	if (flag)
	{
		paths = ft_split(envp[i] + 5, ':');
		return (paths);
	}
	else
		return (NULL);
}

char	**initialize_paths(char *cmd)
{
	char	**paths;

	paths = grab_paths(shell()->env);
	if (!paths)
	{
		rlp_error_msg(cmd);
		return (NULL);
	}
	return (paths);
}

char	*find_path(char *cmd)
{
	char	**paths;
	char	*final_path;
	char	*add_bar;
	int		i;

	paths = initialize_paths(cmd);
	i = -1;
	while (paths[++i])
	{
		add_bar = ft_strjoin(paths[i], "/");
		final_path = ft_strjoin(add_bar, cmd);
		free(add_bar);
		check_dir(cmd, final_path, paths);
		if (!access(final_path, F_OK))
		{
			free_split(paths);
			return (final_path);
		}
		free(final_path);
	}
	rlp_error_msg(cmd);
	free_split(paths);
	return (0);
}

char	*getpath(char *cmd)
{
	if (cmd[0] == '/')
		return (absolute_path(cmd));
	if (cmd[0] && cmd[0] == '.')
		return (search_rpath(cmd));
	else
		return (find_path(cmd));
}
