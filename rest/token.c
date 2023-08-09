/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:25:12 by learodri@st       #+#    #+#             */
/*   Updated: 2023/08/09 16:29:16 by learodri@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../miniheader.h"

//    echo "vai carai seu viado" | wc -l > aqui.txt 

//echo "vai carai" > vai.txt

//lanca na linked list

char *create_it(char *in, int *i)
{
	while (in[*i] && (in[*i] =! ' ' || in[*i] != '\t'))
	{
		i++;
	}
}

void	token_it(char *in, int i) // mesmo contadorr??
{
	int *i;

	while (in[i])
	{
		while (in[i] && (in[i] == ' ' || in[i] == '\t'))
			i++;
		create_it(in, &i);
	}
}