/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_arvo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri <learodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 18:50:55 by learodri          #+#    #+#             */
/*   Updated: 2023/08/24 22:04:44 by learodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../miniheader.h"

void	token_tree()
{
	t_token	*tmp;
	t_token	*tmp2;
	
	int flag;

	tmp = shell()->head;
	if (!tmp)
		return;
	
    printf("\n\n\n\n");

	while (tmp)
	{
		flag = 2;
		while (flag != 0 && (tmp->token[0] != '|' || tmp))
		{
			if (tmp->token == '|' || tmp->next == NULL)
			{
				flag--;
				if(tmp->token == '|' && flag == 0)
				{
					printf("por node");
				}
			}
		}
		
	}

	//manda arvore

	while (tmp)
	{
		if (flag == 2)
		{
			while (tmp && tmp->token != '|')
			{
				if (tmp->token[0] == '<' || tmp->token[0] == '>')
					tmp = tmp->next->next; // porque tem que haver algo aqui, se nao quebra antes de entrar
				//cria node e joga o bagui
				//ve o tipo ou add tipo
				//manda tree
				tmp = tmp->next;
				flag--;
				continue;
				//tmp se mantem ingual e roda linked list again?
			} 
		}
		if (flag == 1)
		{
			
		}
		if(flag == 0)
		{
			
		}
		
	}
}

/*
{
    E_CMD,
    E_PIPE,
    E_IN,
    E_OUT,
    E_APPEND,
    E_HDOC,
    E_BUILT
} t_type;*/

