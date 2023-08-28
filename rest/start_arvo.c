/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_arvo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 18:50:55 by learodri          #+#    #+#             */
/*   Updated: 2023/08/28 20:43:34 by learodri@st      ###   ########.fr       */
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

t_token *for_cmd(t_token *start) // contar quantas strs para matriz, ja manda pra arvore, fodase
{
	t_token *tmp;
	t_node *new;
	int	nb_str;
	int i = 0;
	
	tmp = start;
	new = malloc(sizeof(t_node));
	if (!new)
		return ;

	while (tmp)
	{
		if (tmp->type == 0)
			nb_str++;
		tmp = tmp->next;
	}
	new->nodeType = E_CMD; //checar depois
	new->left = NULL;
	new->right = NULL;
	new->up = NULL;
	new->arguments = malloc(sizeof(char *) * (nb_str + 1));
	if (!new->arguments) //voltar aqui para o final free talbez
	{
		if (new)
			free(new);
		return ; 
	}
	//new->pipe[]
	tmp = start;

	while (tmp)
	{
		if (tmp->token[0] == '|')
		{
			new->arguments[i] = NULL;
			//sent_to_tree(new); - node tem que tar 100% pronto
			return(tmp);
		}
		if (tmp->type == 0)
		{
			new->arguments[i] = ft_strdup(tmp->token);
			if (!new->arguments[i])
			display_error("deu ruim na mtx node-arvore", 0);
			i++;
		}
		tmp = tmp->next;
	}

	new->arguments[i] = NULL;
	//sent_to_tree(new);

	return NULL; // em caso de nao ter mais pipes ou nao ter
	
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
		sent_to_tree(new_node(pipe));
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