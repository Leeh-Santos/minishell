/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:36:54 by learodri@st       #+#    #+#             */
/*   Updated: 2023/10/02 15:53:42 by learodri@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../miniheader.h"

void	print_args(char **token, int fd, int i)
{
	if (!token[i])
		return ;
	while (token[i + 1])
	{
		ft_putstr_fd(token[i++], fd);
		ft_putchar_fd(' ', fd);
	}
	ft_putstr_fd(token[i], fd);
}

void	print_args_nl(char **token, int fd, int i) // ja no fd
{
	if (!token[i]) // se nao tem nada ja joga no echo node so manda um \n
		return (ft_putchar_fd('\n', fd));
	while (token[i + 1]) // vai add o token e o espaco para o proxico
	{
		ft_putstr_fd(token[i++], fd);
		ft_putchar_fd(' ', fd);
	}
	ft_putendl_fd(token[i], fd); // manda str no fd junto com \n ao final
}


int	check_flag(t_node *branch)
{
	int	i;

	i = 0;
	if ((branch->arguments[1] == NULL) || (!branch->arguments[1][0])) //token em null, e sem arg na 2 str
		return (0);
	if (branch->arguments[1][0] != '-') // 1st echo 2st diferente de '-'
		return (0);
	while (branch->arguments[1][++i])
	{
		if (branch->arguments[1][i] != 'n') //nnnnnnnnnnnnnnnnnnnnnnnnnnnn
			return (0);
	}
	return (1);
}

void	echo_func(t_node *branch, int fd)
{
	if (check_flag(branch)) // 
		print_args(branch->arguments, fd, 2);
	else // echo com null node, sem arg, 2 str nao tem '-', ou nao tem sequencia correcta de n - echo normal
		print_args_nl(branch->arguments, fd, 1);
}

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