/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputcheck.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimoes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:56:02 by learodri          #+#    #+#             */
/*   Updated: 2023/10/11 21:59:27 by msimoes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../miniheader.h"

int	quotecheck(char *input, int i, int flag)
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
		return 1; 							//display_error("unclosed quotes bro", 0);
	return 0;
}

int		verify_c(char c, int i, char *in)
{
	int flag;

	flag = skip_spaces(c, &i, &in);
	
	if (c == '|' && ((in[i] == '|') || in[i] == '\0'))
		return 1; 							//display_error("check pipes or redirects syntax error", 0);
	if (c == '|' && ((in[i] == '>') || (in[i] == '<')))
	{
		if(((in[i] == '>' && in[i + 1] == '>') || (in[i] == '<' && in[i + 1] == '<')))
			i++;
		i++;
		while((in[i]) && (in[i] == '\t' || in[i] == ' '))
				i++;
		if(char_checker(in[i]))
			return 1; 							//display_error("check pipes or redirects syntax error", 0);
	}
	if ((c == '<' || c == '>') && !(in[i]))
		return 1; 							//display_error("check pipes or redirects syntax error", 0);
	if (c == '<' && (in[i] == '>' || in[i] == '|'))
		return 1; 							//display_error("check pipes or redirects syntax error", 0);
	if (c == '>' && (in[i] == '<' || in[i] == '|'))
		return 1; 							//display_error("check pipes or redirects syntax error", 0);
	if (c == '>' && (in[i] == '>') && flag)
		return 1; 							//display_error("espaco entre redir", 0);
	if (c == '<' && (in[i] == '<') && flag)
		return 1;							//display_error("espaco entre redir", 0);
	return 0;
}

int	redicheck(char *input, int i)
{
	char	c;
	int j;
	
	j = 0;
	if(input[i] == '|')
		return 1; 							//display_error("pipe ao inicio", 0);
	while ((input[i]) && (input[i] == ' ' || input[i] == '\t'))
	{
		if(input[i + 1] != ' ' || input[i + 1] != '\t')
			if(input[i + 1] == '|')
				return 1; 							//display_error("pipe ao inicio", 0);
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
			j = verify_c(input[i], i + 1, input);
			if (j)
				return 1;
		}
		if (input[i])
			i++;
	}
	return 0;
}

int	forbidenchar(char *input)
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
			return 1; 							//display_error("char que nao pode ai fera", 0);
		if (input[i])
			i++;
	}
	return 0;
}	

int	inputcheck(char *input)
{
	if (quotecheck(input, 0, 0))
	{
		ft_putstr_fd("unclosed quotes\n", STDERR_FILENO);
		shell()->exit_s = 2;
		return 1;
	}
	else if (redicheck(input, 0))
	{
		ft_putstr_fd("syntax error: check pipes or redirects\n", STDERR_FILENO);
		shell()->exit_s = 2;
		return 1;
	}
	else if (forbidenchar(input))
	{
		ft_putstr_fd("forbiden char\n", STDERR_FILENO);
		shell()->exit_s = 2;
		return 1;
	}
	return 0;
}