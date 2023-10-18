/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtexit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri <learodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:53:20 by learodri@st       #+#    #+#             */
/*   Updated: 2023/10/18 19:02:16 by learodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../miniheader.h"

int	num_exit(int num)
{
	if (num >= 0 && num <= 255)
		return (num);
	else
		return (num % 256);
}

int	type_exit(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (ft_isascii(line[i]) && !ft_isdigit(line[i]))
		{
			ft_putstr_fd("exit\n", 1);
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(line, 2);
			ft_putendl_fd(" : numeric argument required", 2);
			return (2);
		}
	}
	i = 0;
	if (ft_isdigit(line[i]))
	{
		ft_putstr_fd("exit\n", 1);
		return (num_exit(ft_atoi(line)));
	}
	return (0);
}

void	exit_it(char **line, char **env)
{
	int	status;
	int	i;

	status = 0;
	i = -1;
	if (!line[1])
	{
		ft_putstr_fd("exit\n", 1);
		status = 0;
	}
	else if (line[1] && line[2])
	{
		shell()->exit_s = 1;
		ft_putstr_fd("exit: too many arguments\n", 1);
		/*while (env[++i])
			free (env[i]);
		free (env);*/
		return ;
	}
	else
		status = type_exit(line[1]);
	while (env[++i])
		free (env[i]);
	free (env);
	free_linked();
	free_na_tree(shell()->root);
	exit (status);
}
