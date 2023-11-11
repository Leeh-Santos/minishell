/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimoes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:25:12 by learodri@st       #+#    #+#             */
/*   Updated: 2023/11/11 07:51:51 by msimoes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniheader.h"
/*
void print2DUtil(t_node* root, int space)
{
    int COUNT = 10;
	
    if (root == NULL)
        return;
 

    space += COUNT;
 
    
    print2DUtil(root->right, space);
 
    
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    //print_node_recebido(root);//printf("%d\n", root->nodeType);
 
    
    print2DUtil(root->left, space);
}

void print2D(t_node* root)
{
    print2DUtil(root, 0);
}
*/

void	facin(char *in, char *tmp, int *i)
{
	int	k;
	int	quote;

	quote = 0;
	k = 0;
	while ((in[*i]))
	{
		if (is_redir_pipe(in[*i]))
			break ;
		if (in[*i] == 39 || in[*i] == '"')
			quote++;
		if (quote % 2 == 0)
			if ((in[*i] == ' ') || ((in[*i] == '\t')))
				break ;
		tmp[k] = in[*i];
		(*i)++;
		k++;
	}
	tmp[k] = '\0';
}

char	*take_w(char *in, int *i)
{
	char	*tmp;

	tmp = malloc(999 * sizeof(char));
	if (!tmp)
		return (NULL);
	while (in[*i])
	{
		if (in[*i] == 39 || in[*i] == '"')
			aspasword(in, tmp, i);
		else if (in[*i] == '|' || in[*i] == '<' || in[*i] == '>')
			delword(in[*i], in, tmp, i);
		else if (in[*i])
			facin(in, tmp, i);
		break ;
	}
	return (tmp);
}

void	killspc(char *in, int *i)
{
	while ((in[*i]) && (in[*i] == ' ' || in[*i] == '\t'))
		(*i)++;
}

void	insert(char *in)
{
	t_token	*new;
	t_token	*tmp;

	new = malloc(sizeof(t_token));
	if (!new)
		display_error("deu pau no malloc", 0);
	in = expand_check(in, shell()->env);
	new->token = in;
	new->type = 0;
	new->next = NULL;
	tmp = shell()->head;
	if (!tmp)
	{
		shell()->head = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

//print2D(shell()->root);
void	token_it(char *in)
{
	int	i;

	i = 0;
	shell()->root = NULL;
	while (in[i] != '\0')
	{
		killspc(in, &i);
		if (in[i] == '\0')
			break ;
		insert(take_w(in, &i));
		del_emptyquotes();
	}
	token_type();
	update_quote();
	token_tree(shell()->head);
}
