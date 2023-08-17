/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:25:12 by learodri@st       #+#    #+#             */
/*   Updated: 2023/08/17 10:34:40 by learodri@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../miniheader.h"


void	aspasword(char *in, char *tmp, int *i, char c)
{
	int	k;
	int	flag;

	k = 0;
	flag = 0;
	while(in[*i])
	{
		if(in[*i] == c && flag)
		{
			tmp[k] = c;
			tmp[k + 1] = '\0';
			(*i)++;
			return;
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
	}else if (c == '<')
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

	k = 0;
	while((in[*i]))
	{
		if ((in[*i] == '|') || (in[*i] == '>') || (in[*i] == '<') || (in[*i] == ' ') || (in[*i] == '\t') || (in[*i] == 39) || (in[*i] == '"'))
		{
			break;
		}
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
		else if(in[*i] >= 35 && in[*i] <= 126)
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
	new->token = in;
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
void	token_it(char *in)
{
	int i;

	i = 0;
	while (in[i] != '\0')
	{
		killspc(in, &i);
		if (in[i] == '\0')
			return;
		insert(take_w(in, &i));
	}
	
}