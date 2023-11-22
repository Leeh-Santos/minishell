/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri <learodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:36:54 by learodri@st       #+#    #+#             */
/*   Updated: 2023/11/22 18:34:54 by learodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniheader.h"

void	print_args(char **token, int fd, int i)
{
	int	print;

	print = 0;
	if (!token[i])
		return ;
	while (token[i])
	{
		if (ft_strncmp(token[i], "-n", 2) != 0 || \
		(ft_strncmp(token[i], "-n", 2) == 0 && ft_strlen(token[i]) != 2))
			print = 1;
		if (print)
		{
			ft_putstr_fd(token[i], fd);
			if (token[i + 1])
				ft_putchar_fd(' ', fd);
		}
		i++;
	}
}

//line 41: ja no fd
//line 43: se nao tem nada ja joga no echo node so manda um \n
//line 45: vai add o token e o espaco para o proxico
//line 50: manda str no fd junto com \n ao final
void	print_args_nl(char **token, int fd, int i)
{
	if (!token[i])
		return (ft_putchar_fd('\n', fd));
	while (token[i + 1])
	{
		ft_putstr_fd(token[i++], fd);
		ft_putchar_fd(' ', fd);
	}
	ft_putendl_fd(token[i], fd);
}

//line 61: token em null, e sem arg na 2 str
//line 63: 1st echo 2st diferente de '-'
//line 67: resolve -nnnnnnnnnnnnn
int	check_flag(t_node *branch)
{
	int	i;

	i = 0;
	if ((branch->arguments[1] == NULL) || (!branch->arguments[1][0]))
		return (0);
	if (branch->arguments[1][0] != '-')
		return (0);
	while (branch->arguments[1][++i])
	{
		if (branch->arguments[1][i] != 'n')
			return (0);
	}
	return (1);
}

//line 79: echo com null node, sem arg, 2 str nao tem '-',
//ou nao tem sequencia correcta de n - echo normal
void	echo_func(t_node *branch, int fd)
{
	if (check_flag(branch))
		print_args(branch->arguments, fd, 2);
	else
		print_args_nl(branch->arguments, fd, 1);
}
