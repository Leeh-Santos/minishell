/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_arvo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 18:50:55 by learodri          #+#    #+#             */
/*   Updated: 2023/08/28 16:54:30 by learodri@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../miniheader.h"

void	token_type(void)
{
	t_token	*tmp;

	tmp = shell()->head;
	if (!tmp)
		return ;

	while(tmp)
	{
		if (tmp->token[0] == '<' || tmp->token[0] == '>')
		{
			tmp->type = 1;
			if (tmp->next)
				tmp->next->type = 1;
		}
		tmp = tmp->next;
	}
}

t_node *newnode()
{

}

t_token *for_cmd(t_token *start) // contar quantas strs para matriz, 
{
	t_token *tmp;
	
	tmp = start;

	while (tmp)
	{
		if (tmp->token[0] == '|')
			return(tmp);
		
	}
	
}

t_node *token_tree(t_token *head)
{
	t_token	*tmp;
	t_token	*pipe;
	
	pipe = NULL;
	tmp = head;
	if (!tmp)
		return;

	pipe = for_cdm(tmp); //manda node para arvore
	for_redir(tmp); // manda node para arover

	if (pipe)
	{
		insert_tr(new_node(pipe));
		token_tree(pipe);
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

/*while (tmp)
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
		
	}*/