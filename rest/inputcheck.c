/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputcheck.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri <learodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:56:02 by learodri          #+#    #+#             */
/*   Updated: 2023/06/27 19:06:24 by learodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../miniheader.h"

void	quotecheck(char *input, int i)
{
	char quote;
	int flag;
	
	flag = 0;
	while (input[i])
	{
		if (input[i] == 39 || input[i] == '"')
		{
			quote = input[i];
			flag = 1;
			i++;
			while(input[i])
			{
				if (input[i] == quote)
				{
					flag = 0;
					break;
				}
				i++;
			}
		}
		i++;
	}
	if (flag)
		display_error("unclosed quotes bro", 1);
}

void	inputcheck(char *input)
{
	quotecheck(input, 0);
}