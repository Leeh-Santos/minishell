/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:51:11 by learodri          #+#    #+#             */
/*   Updated: 2023/08/14 15:07:53 by learodri@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "miniheader.h"


void	envparse(char **envp)
{
	int i;
	
	i = 0;
	while(envp[i])
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

int	main(int argc, char *argv[] ,char **envp)
{
	char *input;

	(void)argc;
	(void)argv;
	envparse(envp);
	shell()->head =	NULL;
	while (1)
	{
		//signal(SIGINT, handle_sigint);
		input = readline("minishell$ ");
		inputcheck(input);
		if (input && *input)
		{
			add_history(input);
			//token_it(input, 0);
		}
		free(input);
	}
	return 0;
}