/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:06:47 by learodri@st       #+#    #+#             */
/*   Updated: 2023/09/19 16:47:52 by learodri@st      ###   ########.fr       */
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

char	*relative_normal(char *cmd)
{
	if (cmd[0] && cmd[0] == '.')
		return (search_rpath(cmd));

}

char	*getpath(char *cmd)
{
	if (cmd[0] == '/')
		return (absolute_path(cmd));
	else
		return (relative_normal(cmd));
}