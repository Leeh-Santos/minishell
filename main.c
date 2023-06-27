/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:51:11 by learodri          #+#    #+#             */
/*   Updated: 2023/06/27 15:59:09 by learodri@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheader.h"

void envparse(char **envp)
{
	int i;
	
	i = 0;
	while(envp[i])
		i++;
	if (shell()->env)
		free(shell()->env);
	shell()->env = malloc(sizeof(char *) * (i + 1));
	if (!shell()->env)
	{	
		perror("env mtx deu ruim");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (envp[i])
	{
		shell()->env[i] = ft_strdup(envp[i]);
		if (!shell()->env[i])
		{	
			perror("env mtx deu ruim");
			exit(EXIT_FAILURE);
		}
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
	printf("%s \n", shell()->path);
	while (1)
	{
		//signal(SIGINT, handle_sigint);
		input = readline("minishell$ ");
		//inputcheck(input);
		printf("\n%s ", input);
		
	}
	return 0;
}