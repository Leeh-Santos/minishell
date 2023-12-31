/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_arvo_support.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:18:54 by learodri@st       #+#    #+#             */
/*   Updated: 2023/09/04 16:50:19 by learodri@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../miniheader.h"

int	check_redir_node(t_node *node)
{
	if (!node)
		return (0);
	if (node->nodeType >= E_IN && node->nodeType <= E_HDOC)
		return (1);
	return (0);
}

int	check_pipe_node(t_node *node)
{
	if (!node)
		return (0);
	if (node->nodeType == E_PIPE)
		return (1);
	return (0);
}

int	check_cmd_node(t_node *node)
{
	if (!node)
		return (0);
	if (node->nodeType == E_CMD || node->nodeType == E_BUILT)
		return (1);
	return (0);
}
