/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_arvo3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimoes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 21:57:41 by msimoes-          #+#    #+#             */
/*   Updated: 2023/11/10 21:57:41 by msimoes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniheader.h"

int	built_ou_cmd(t_token *node)
{
	if (!ft_strncmp(node->token, "echo", 5))
		return (E_BUILT);
	if (!ft_strncmp(node->token, "cd", 3))
		return (E_BUILT);
	if (!ft_strncmp(node->token, "pwd", 4))
		return (E_BUILT);
	if (!ft_strncmp(node->token, "export", 7))
		return (E_BUILT);
	if (!ft_strncmp(node->token, "unset", 6))
		return (E_BUILT);
	if (!ft_strncmp(node->token, "env", 4))
		return (E_BUILT);
	if (!ft_strncmp(node->token, "exit", 5))
		return (E_BUILT);
	return (E_CMD);
}

void	token_type(void)
{
	t_token	*tmp;

	tmp = shell()->head;
	if (!tmp)
		return ;
	while (tmp)
	{
		if (tmp->token[0] == '|')
			tmp->type = -1;
		if (tmp->token[0] == '<' || tmp->token[0] == '>')
		{
			tmp->type = 1;
			if (tmp->next)
				tmp->next->type = 1;
		}
		tmp = tmp->next;
	}
}

//print_node_recebido(node);
void	send_to_tree(t_node *node)
{
	if (check_redir_node(node))
		where_redir(node);
	else if (check_cmd_node(node))
		where_cmd(node);
	else if (check_pipe_node(node))
		add_on_top(node);
}
