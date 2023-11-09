/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimoes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:06:47 by learodri@st       #+#    #+#             */
/*   Updated: 2023/11/09 03:04:12 by msimoes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniheader.h"

void	check_dir(char *str, char *path, char **paths)
{
	struct stat	buf;

	ft_memset(&buf, 0, sizeof(buf));
	lstat(path, &buf);
	if (S_ISDIR(buf.st_mode))
	{
		ft_putstr_fd(str, 2);
		ft_putendl_fd(" is a directory", 2);
		free_linked();
		free_na_tree(shell()->root);
		free_no_env();
		free(path);
		free_split(paths);
		shell()->exit_s = 126;
		exit(shell()->exit_s);
	}
}

void	rlp_error_msg(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": Command not found", 2);
}

char	*absolute_path(char *cmd)
{
	DIR	*dir;

	dir = opendir(cmd);
	if (dir)
	{
		closedir(dir);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(" is a directory", 2);
		free_linked();
		free_na_tree(shell()->root);
		free_no_env();
		shell()->exit_s = 126;
		exit(shell()->exit_s);
	}
	if (access(cmd, X_OK) < 0)
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": Command not found", 2);
		free_linked();
		free_na_tree(shell()->root);
		free_no_env();
		shell()->exit_s = 127;
		exit(shell()->exit_s);
	}
	return (cmd);
}

//para retornar com path ok
int	is_path(char *str, char *path)
{
	struct stat	buf;

	if (!path)
		return (0);
	ft_memset(&buf, 0, sizeof(buf));
	lstat(path, &buf);
	if (S_ISDIR(buf.st_mode))
	{
		ft_putstr_fd(str, 2);
		ft_putendl_fd(" is a directory", 2);
		shell()->exit_s = 126;
		free_linked();
		free_na_tree(shell()->root);
		free_no_env();
		free(path);
		exit(shell()->exit_s);
	}
	if (access(path, X_OK) >= 0)
		return (1);
	return (0);
}

char	*search_rpath(char *cmd)
{
	char	*path;
	char	*tmp;

	path = NULL;
	tmp = NULL;
	path = getcwd(NULL, 0);
	tmp = ft_strjoin(path, "/");
	free(path);
	path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (is_path(cmd, path))
		return (path);
	free(path);
	rlp_error_msg(cmd);
	return (NULL);
}

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

char	*find_path(char *cmd)
{
	char	**paths;
	char	*final_path;
	char	*add_bar;
	int		i;

	paths = grab_paths(shell()->env);
	if (!paths)
	{
		rlp_error_msg(cmd);
		return (NULL);
	}
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
