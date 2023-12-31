/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:25:12 by learodri@st       #+#    #+#             */
/*   Updated: 2023/10/19 11:59:18 by learodri@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../miniheader.h"

static int is_redir_pipe(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return 1;
	return 0;
}

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
    print_node_recebido(root);//printf("%d\n", root->nodeType);
 
    
    print2DUtil(root->left, space);
}
 

void print2D(t_node* root)
{
    print2DUtil(root, 0);
}

void	aspasword(char *in, char *tmp, int *i, char c)
{
	int	k;
	int	flag;
	int quote;

	k = 0;
	flag = 0;
	quote = 0;
	while(in[*i])
	{
		if(in[*i] == c && flag)
		{
			flag = 0;
			tmp[k++] = c;
			if (in[*i + 1] == ' ' || in[*i + 1] == '\t' || in[*i + 1] == '\0' || is_redir_pipe(in[*i + 1]))
			{
				tmp[k] = '\0';
				(*i)++;
				return;
			}
			else
			{
				(*i)++;
				while (in[*i] && (in[*i] >= 32 && in[*i] <= 126))
				{
					if(in[*i] == 39 || in[*i] == '"')
						quote++;
					if(quote % 2 == 0 && (in[*i] == ' ' || in[*i] == '\t' || is_redir_pipe(in[*i])))
						break;
					tmp[k] = in[*i];
					(*i)++;
					k++;
				}
				tmp[k] = '\0';
				return;
			}
		}
		flag = 1;
		tmp[k] = in[*i];
		(*i)++;
		k++;
	}
}

void	delword(char c, char *in, char *tmp, int *i)
{
	int	k;

	k = 0;
	if (c == '|')
	{
		tmp[k] = c;
		tmp[k + 1] ='\0';
		(*i)++;
		return;
	}
	else if (c == '>')
	{
		if (in[*i + 1] == '>')
		{
			tmp[k] = c;
			tmp[k + 1] = c;
			tmp[k + 2] = '\0';
			(*i) += 2;
			return;
		}
		tmp[k] = c;
		tmp[k + 1] = '\0';
		(*i)++;
		return;
	}
	else if (c == '<')
	{
		if (in[*i + 1] == '<')
		{
			tmp[k] = c;
			tmp[k + 1] = c;
			tmp[k + 2] = '\0';
			(*i) += 2; //proteger nesses casos
			return;
		}
		tmp[k] = c;
		tmp[k + 1] = '\0';
		(*i)++;
		return;
	}
}

void	facin(char *in, char *tmp, int *i)
{
	int	k;
	int quote;

	quote = 0;
	k = 0;
	while((in[*i]))
	{
		if(is_redir_pipe(in[*i]))
			break;
		if(in[*i] == 39 || in[*i] == '"')
			quote++;
		if(quote % 2 == 0)
			if ((in[*i] == ' ') || ((in[*i] == '\t')))
				break;
		tmp[k] = in[*i];
		(*i)++;
		k++;
	}
	tmp[k] = '\0';
	

}

char	*take_w(char *in, int *i) // sempre cai aqui no 1 index da subs
{
	char	*tmp = malloc(999 * sizeof(char));
	
	if(!tmp)
		return NULL;
		
	while(in[*i])
	{
		if(in[*i] == 39 || in[*i] == '"')
			aspasword(in, tmp, i, in[*i]);
		else if(in[*i] == '|' || in[*i] == '<'  || in[*i] == '>')
			delword(in[*i],in, tmp, i);
		else if(in[*i])
			facin(in, tmp, i);
		break; // tava travado aqui antes no oioioi
	}
	return (tmp);
	
}

void	killspc(char *in, int *i)
{

	while ((in[*i]) && (in[*i] == ' '))
	{
		(*i)++;
	}
}

void	insert(char *in)
{
	t_token	*new;
	t_token	*tmp;

	new = malloc(sizeof(t_token));
	if (!new)
		display_error("deu pau no malloc", 0);
	in = expand_check(in, shell()->env);
	new->token = in; //tratar do expand
	new->type = 0;
	new->next = NULL;
	tmp = shell()->head;
	if (!tmp)
	{
		shell()->head = new;	
		return;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	
}

void	update_quote(void)
{
	t_token *tmp;

	tmp = shell()->head;
	if (!tmp)
		return;
	while (tmp)
	{
		tmp->token = del_quotes(tmp->token);
		tmp = tmp->next;
	}
}

void	token_it(char *in)
{
	int i;

	i = 0;
	shell()->root = NULL;
	while (in[i] != '\0')
	{
		killspc(in, &i);
		if (in[i] == '\0')
			break;
		insert(take_w(in, &i));
		del_emptyQuotes();
	}
	token_type();
	update_quote();
	token_tree(shell()->head); 
	print2D(shell()->root);
}