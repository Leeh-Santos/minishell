/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri <learodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:51:11 by learodri          #+#    #+#             */
/*   Updated: 2023/09/19 18:08:39 by learodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "miniheader.h"

void	print_token();


void	envparse(char **envp) // essa poha gurda o env inteirp e o PATH
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

int	main(int argc, char **argv ,char **envp)
{
	char *input;

	(void)argc;
	(void)argv;
	envparse(envp);
	shell()->head =	NULL;
	while (1)
	{
		//signal(SIGINT, handle_sigint);
		input = readline("picashell$ ");
		inputcheck(input); // case der erro de syntax, fazer dar free e volvar a inputline
		if (input && *input)
		{
			add_history(input);
			token_it(input);
			//checkar input ante de criar arvore, redir sem arg, checa com linked
			print_token();
			exec_tree();// quebra quando eu chamo
		}
		free_linked();
		free(input);
		
	}
	return 0;
}

void	print_token(){
	
	t_token *tmp = shell()->head;

	int i = 0;
	
	printf("\n");

	while (tmp){
		printf("linkedlistnode %d -- %s -- id:%d\n", i, tmp->token, tmp->type);
		tmp = tmp->next;
		i++;
	}

}