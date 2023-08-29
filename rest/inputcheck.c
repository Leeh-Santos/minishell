/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputcheck.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimoes- <msimoes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:56:02 by learodri          #+#    #+#             */
/*   Updated: 2023/08/29 20:07:37 by msimoes-         ###   ########.fr       */
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
		display_error("unclosed quotes bro", 0);
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
	//falta: echo ola |>> |<<
	if (c == '|' && (in[i] == '|'))
		display_error("check pipes or redirects syntax error", 0);
	if (c == '|' && ((in[i] == '>') || (in[i] == '<')))
	{
		while((in[i++]) && (in[i] == '\t' || in[i] == ' '))
			i++;
		if(char_checker(in[i]))
			display_error("check pipes or redirects syntax error", 0);
	}
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
	char	c;
	
	if(input[i] == '|')
		display_error("pipe ao inicio", 0);
	while ((input[i]) && (input[i] == ' ' || input[i] == '\t'))
	{
		if(input[i + 1] != ' ' || input[i + 1] != '\t')
			if(input[i + 1] == '|')
				display_error("pipe ao inicio", 0);
		i++;
	}
	while (input[i])
	{
		if (input[i] == '"' || input[i] == 39)
		{
			c = input[i];
			if (input[i])
				i++;
			while (input[i] && input[i] != c)
				i++;
		}
		if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			shell()->nb_pipe++;
			verify_c(input[i], i + 1, input);
		}
		if (input[i])
			i++;
	}
}

void	forbidenchar(char *input)
{
	int i;
	char c;

	i = 0;

	while (input[i])
	{
		if (input[i] == 39 || input[i] == '"')
		{
			c = input[i];
			if (input[i])
				i++;
			while (input[i] && input[i] != c)
				i++;
		}
		if (input[i]== ';' || input[i] == '\\' || input[i] == '[' || input[i] == ']' || input[i] == '{'
		|| input[i] == '}' || input[i] == '(' || input[i] == ')')
			display_error("char que nao pode ai fera", 0);
		if (input[i])
			i++;
	}
}

void	inputcheck(char *input)
{
	quotecheck(input, 0, 0);
	redicheck(input, 0);
	forbidenchar(input);
}