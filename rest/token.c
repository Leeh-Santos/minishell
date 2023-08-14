/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:25:12 by learodri@st       #+#    #+#             */
/*   Updated: 2023/08/14 16:56:36 by learodri@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../miniheader.h"

/*void	create_it(char *in, int *i)
{
	char	tmp[999];
	char c;
	
	while (in[*i] && (in[*i] =! ' ' || in[*i] != '\t'))
	{
		if (in[*i] == 39 || in[*i] == '"')
		{
			tmp[*i] = in[*i]; 
			c = in[*i];
			i++;
			while (in[*i] != c) // cai dentro das aspas
			{
				tmp[*i] = in[*i];
				i++;
			}
			tmp[*i + 1] = c;
			tmp[*i + 2] = '\0';
		}
		
		if (in[*i])
			i++;
	}
}*/

char 	*aspasword(char *in, char *tmp, int *i, char c)
{
	
}

char	*take_w(char *in, int *i) // sempre cai aqui no 1 index da subs
{
	char	*tmp = malloc(999 * sizeof(char));
	int	k;

	if(!tmp)
		return NULL;
	k = 0;
	
	while(in[*i])
	{
		if(in[*i] == 39 || in[*i] == '"')
			tmp = aspasword(in, tmp, i, in[*i]);
		else if(in[*i] == '|' || in[*i] == '<'  || in[*i] == '>')
			tmp = delword(in, tmp, i);
		else if(in[*i] >= 35 && in[*i] <= 126)
			tmp = facin(in, tmp);                             // avanca ate bater no pipe ou del e devolve a palavra, mandra outra vez no loop
	}
	return (tmp); // cuidado de nao tiver nada aqui
	
}

void	killspc(char *in, int *i)
{

	while(in && (in[*i] == ' ') || (in[*i] == '\t'))
	{
		(*i)++;
	}
}

void	token_it(char *in) // mesmo contadorr??
{
	int i;

	while (in)
	{
		killspc(in, &i);
		insert(take_w(in, &i));
	}
	
}