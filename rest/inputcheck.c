/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputcheck.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:56:02 by learodri          #+#    #+#             */
/*   Updated: 2023/07/05 16:36:03 by learodri@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../miniheader.h"

void	quotecheck(char *input, int i, int flag)
{
	char quote;

	while (input[i])
	{
		if (input[i] == 39 || input[i] == '"')
		{
			quote = input[i];
			flag = 1;
			i++;
			while (input[i])
			{
				if (input[i] == quote)
				{
					flag = 0;
					break;
				}
				i++;
			}
		}
		if (input[i])
			i++;
	}
	if (flag)
		display_error("unclosed quotes bro", 1);
}

void		verify_c(char c, int i, char *in)
{
	int flag;

	flag = 0;
	while((in[i]) && (in[i] == '\t' || in[i] == ' ')){
		if ((c == '>' || c == '<') && (in[i] == '\t' || in[i] == ' '))
			flag++;
		i++;
	}
		
	if (c == '|' && (in[i] == '|'))
		display_error("check pipes or redirects syntax error", 0);
	if (c == '<' && (in[i] == '>' || in[i] == '|'))
		display_error("check pipes or redirects syntax error", 0);
	if (c == '>' && (in[i] == '<' || in[i] == '|'))
		display_error("check pipes or redirects syntax error", 0);
	if (c == '>' && (in[i] == '>') && flag)
		display_error("espaco entre redir", 0);
	if (c == '<' && (in[i] == '<') && flag)
		display_error("espaco entre redir", 0);	
}

void	redicheck(char *input, int i)
{

	while (input[i])
	{
		if (input[i] == '|' || input[i] == '>' || input[i] == '<')
			verify_c(input[i], i + 1, input);
		i++;
	}
}

void	inputcheck(char *input)
{
	quotecheck(input, 0, 0);
	redicheck(input, 0);
}