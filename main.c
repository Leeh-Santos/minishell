/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:51:11 by learodri          #+#    #+#             */
/*   Updated: 2023/08/16 20:54:47 by learodri@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "miniheader.h"


/// dando pau no espaco|espaco
///dando pau com char e espaco no final


void	print_token();


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
			token_it(input);
			print_token();	
		}
		free(input);
		free_linked();
	}
	return 0;
}

void	print_token(){
	
	t_token *tmp = shell()->head;

	while (tmp){
		printf("direto da lista - %s\n", tmp->token);
		tmp = tmp->next;
	}
}