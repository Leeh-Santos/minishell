/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri <learodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:57:54 by learodri@st       #+#    #+#             */
/*   Updated: 2023/10/30 19:47:50 by learodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../miniheader.h"

void	sig_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

int	exit_signal(int status, int flag)
{
	int		ret;

	ret = 0;
	if (flag == 1)
	{
		ret = status;
		shell()->exit_s = status;
	}
	if (flag == 3)
		ret = 0;
	
	return (ret);
}

void	sig_int2(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putstr_fd("chupa carai\n", 1);
		rl_on_new_line();
		rl_redisplay();
		if (shell()->root)
			free_na_tree(shell()->root);
		if (shell()->head)
			free_linked();
		if (shell()->env)
			free_no_env();
		if (shell()->path1)
			free(shell()->path1);
		if (shell()->tmp)
			free(shell()->tmp);
		shell()->exit_s = 130;
		exit(shell()->exit_s);
	}
}

void	sig_int(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_redisplay();
		exit_signal(130, 1);
	}
}


void	signal_in(int sig, void (*func)())
{
	struct sigaction	sigs;

	sigemptyset(&(sigs.sa_mask));
	sigs.sa_flags = 0;
	sigs.sa_handler = func;
	if (sigaction(sig, &sigs, NULL) == -1)
		sig_error("ERROR: sigaction\n");
}