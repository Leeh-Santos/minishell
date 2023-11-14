/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_arvo_support.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:18:54 by learodri@st       #+#    #+#             */
/*   Updated: 2023/11/14 14:34:27 by learodri@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniheader.h"

int	check_redir_node(t_node *node)
{
	if (!node)
		return (0);
	if (node->nodetype >= E_IN && node->nodetype <= E_HDOC)
		return (1);
	return (0);
}

int	check_pipe_node(t_node *node)
{
	if (!node)
		return (0);
	if (node->nodetype == E_PIPE)
		return (1);
	return (0);
}

int	check_cmd_node(t_node *node)
{
	if (!node)
		return (0);
	if (node->nodetype == E_CMD || node->nodetype == E_BUILT)
		return (1);
	return (0);
}
