/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:51:11 by learodri          #+#    #+#             */
/*   Updated: 2023/06/22 16:25:19 by learodri@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniheader.h"

void envparse(char **envp)
{
	int i;

	i = 0;
	best_envs(); // for others
	while(envp[i])
		i++;

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