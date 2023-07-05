/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:51:11 by learodri          #+#    #+#             */
/*   Updated: 2023/07/05 15:56:28 by learodri@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "miniheader.h"

//checkar redirects < para dps aplicar logica ---- | > | < só cria doc.
//com espaco >  > nao aceita >>somente junto 

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
	while (1)
	{
		//signal(SIGINT, handle_sigint);
		input = readline("minishell$ ");
		inputcheck(input);
		if (input && *input)
			add_history(input);
		free(input);
	}
	return 0;
}