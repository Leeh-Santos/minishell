/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputcheck.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimoes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:56:02 by learodri          #+#    #+#             */
/*   Updated: 2023/11/09 02:57:07 by msimoes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniheader.h"

int	is_special_combination(char c, char next, int flag)
{
	if ((c == '<' || c == '>') && !next)
		return (1);
	if (c == '<' && (next == '>' || next == '|'))
		return (1);
	if (c == '>' && (next == '<' || next == '|'))
		return (1);
	if (c == '>' && (next == '>') && flag)
		return (1);
	if (c == '<' && (next == '<') && flag)
		return (1);
	return (0);
}

int	verify_c(char c, int i, char *in)
{
	int	flag;

	flag = skip_spaces(c, &i, &in);
	if (c == '|' && ((in[i] == '|') || in[i] == '\0'))
		return (1);
	if (c == '|' && ((in[i] == '>') || (in[i] == '<')))
	{
		if (((in[i] == '>' && in[i + 1] == '>') || \
		(in[i] == '<' && in[i + 1] == '<')))
			i++;
		i++;
		while ((in[i]) && (in[i] == '\t' || in[i] == ' '))
				i++;
		if (char_checker(in[i]))
			return (1);
	}
	if (is_special_combination(c, in[i], flag))
		return (1);
	return (0);
}

int	check_pipe_prefix(const char *input, int i)
{
	if (input[i] == '|')
		return (1);
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
	{
		if (input[i + 1] != ' ' && input[i + 1] != '\t')
		{
			if (input[i + 1] == '|')
				return (1);
		}
		i++;
	}
	return (0);
}

int	redicheck(char *input, int i, int j)
{
	char	c;

	if (check_pipe_prefix(input, i))
		return (1);
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
			j = verify_c(input[i], i + 1, input);
			if (j)
				return (1);
		}
		if (input[i])
			i++;
	}
	return (0);
}	

int	inputcheck(char *input)
{
	if (quotecheck(input, 0, 0))
	{
		ft_putstr_fd("unclosed quotes\n", STDERR_FILENO);
		shell()->exit_s = 2;
		return (1);
	}
	else if (redicheck(input, 0, 0))
	{
		ft_putstr_fd("syntax error: check pipes or redirects\n", STDERR_FILENO);
		shell()->exit_s = 2;
		return (1);
	}
	else if (forbidenchar(input))
	{
		ft_putstr_fd("forbiden char\n", STDERR_FILENO);
		shell()->exit_s = 2;
		return (1);
	}
	return (0);
}
