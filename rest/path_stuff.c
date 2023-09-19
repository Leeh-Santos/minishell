/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri <learodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:06:47 by learodri@st       #+#    #+#             */
/*   Updated: 2023/09/19 18:49:29 by learodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../miniheader.h"

char	*absolute_path(char *cmd)
{
	DIR	*dir;

	dir = opendir(cmd);
	if (dir)
	{
		closedir(dir);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(" is a directory", 2);
		//add exit status
		//chamar exit();
		return NULL;
	}
	if (access(cmd, X_OK) < 0)
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": Command not found", 2);
		//add exit status
		//chamar exit();
		return NULL;
	}
	return (cmd);
}

int	is_path(char *str, char *path) //paara retornar com path ok
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
		//change exit status
		//exit()
	}
	if (access(path, X_OK) >= 0)
		return (1);
	return (0);
}

char	*search_rpath(char *cmd)
{
	char *path;
	char *tmp;

	path = NULL;
	tmp = NULL;
	path = getcwd(NULL, 0);
	tmp = ft_strjoin(path, "/");
	free(path);
	path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (is_path(cmd, path))
		return (path);
	return (NULL);
}

char	**grab_paths(char **envp)
{
	char	**paths;
	int		i;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4)) 
		i++;
	paths = ft_split(envp[i] + 5, ':');
	return (paths);
}

char	*find_path(char *cmd)
{
	char	**paths;
	char	*final_path;
	char	*add_bar;
	int		i;
	

	paths = grab_paths(shell()->env);
	i = -1;
	while (paths[++i])
	{
		add_bar = ft_strjoin(paths[i], "/"); // add bar at the end of each possible path
		final_path = ft_strjoin(add_bar, cmd); // add (ex. "ls") after the end of each path
		free(add_bar);
		if (!access(final_path, F_OK))
		{
			free_split(paths);
			return (final_path);
		}
		free(final_path);
	}
	rlp_error_msg(cmd); // correu todo e nao achou no access
	free_split(paths);
	return (0);
}

void	rlp_error_msg(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": Command not found", 2);
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