/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimoes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:51:11 by learodri          #+#    #+#             */
/*   Updated: 2023/11/07 21:26:07 by msimoes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheader.h"

void	print_token()
{
	t_token *tmp = shell()->head;

	int i = 0;
	
	printf("\n");

	while (tmp){
		printf("linkedlistnode %d -- %s -- id:%d\n", i, tmp->token, tmp->type);
		tmp = tmp->next;
		i++;
	}

}
void	bye_shell(void)
{
	int	i;

	i = 0;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	rl_clear_history();
	while (shell()->env[i])
	{
		free(shell()->env[i]);
		i++;
	}
	if (shell()->env)
		free(shell()->env);
	exit(shell()->exit_s);
}

void	envparse(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	if (shell()->env)
		free(shell()->env);
	shell()->env = malloc(sizeof(char *) * (i + 1));
	if (!shell()->env)
		display_error("env mtx deu ruim", 0);
	i = 0;
	while (envp[i])
	{
		shell()->env[i] = ft_strdup(envp[i]);
		if (!shell()->env[i])
			display_error("env mtx deu ruim", 0);
		i++;
	}
	shell()->env[i] = NULL;
	shell()->path = getenv("PATH");
}

void	main_loop(void)
{
	char	*input;
	int		validation;

	shell()->head = NULL;
	shell()->exit_s = 0;
	while (1)
	{
		signal_in(SIGQUIT, SIG_IGN);
		signal_in(SIGINT, sig_int);
		input = readline("picashell$ ");
		if (!input)
			bye_shell();
		if (input && *input)
		{
			validation = inputcheck(input);
			add_history(input);
			if (!validation)
			{
				token_it(input);
				print_token();
				exec_tree();
			}
		}
		free_linked();
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	envparse(envp);
	main_loop();
	return (0);
}
