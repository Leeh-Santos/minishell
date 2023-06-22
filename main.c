/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri <learodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:51:11 by learodri          #+#    #+#             */
/*   Updated: 2023/06/22 20:43:21 by learodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheader.h"

void envparse(char **envp)
{
	int i;
	

	i = 0;
	while(envp[i])
		i++;
	shell()->env = (char**)malloc(sizeof(char*) * i);
	if (!shell()->env)
	{	
		perror("env mtx deu ruim");
		exit(EXIT_FAILURE);
	}

	while (envp[i])
	{
		shell()->env[i] = malloc(sizeof(char*) * (ft_strlen(envp[i]) + 1));
		if (!shell()->env[i])
		{	
			perror("env mtx deu ruim");
			exit(EXIT_FAILURE);
		}
		ft_strcpy(shell()->env[i], envp[i]);
		i++;
		
	}

	

}

int	main(int argc, char *argv[] ,char **envp)
{
	//char *input;

	(void)argc;
	(void)argv;
	envparse(envp);
	/*while (1)
	{
		input = readline("minishell$ ");
		printf("\n%s ", input);
		
	}*/

	
	return 0;
}