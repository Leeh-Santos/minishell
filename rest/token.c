/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri <learodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:25:12 by learodri@st       #+#    #+#             */
/*   Updated: 2023/08/09 21:04:33 by learodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../miniheader.h"

// echo "vai carai seu viado" | wc -l > aqui.txt 

//echo "vai carai seu viado"|wc -l >aqui.txt 

//echo "vai carai" > vai.txt

//lanca na linked list



void	create_it(char *in, int *i)
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
			tmp [*i + 2] = '\0';
		}
		
		if (in[*i])
			i++;
	}
}

void	token_it(char *in, int i) // mesmo contadorr??
{
	int *i;

	while (in[i] && (in[i] == ' ' || in[i] == '\t'))
	{
		i++;
		create_it(in, &i);
	}
	
}