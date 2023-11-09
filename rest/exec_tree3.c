/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimoes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:30:51 by learodri          #+#    #+#             */
/*   Updated: 2023/11/09 02:30:09 by msimoes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniheader.h"

void	handle_redirection(t_node *node, int key, t_try *bora)
{
	if (key)
		dale_redir2(node, bora);
	else
		dale_redir(node);
}

void	handle_builtin(t_node *node, char *path)
{
	which_builtin(node, 1);
	shell()->exit_s = 0;
	free(path);
	free_linked();
	free_no_env();
	free_na_tree(shell()->root);
	exit(shell()->exit_s);
}

void	handle_execution(t_node *node, char **env_cpy, char *path)
{
	if (path)
		execve(path, node->arguments, env_cpy);
	free(path);
	shell()->exit_s = 127;
	if (node->pipe[1])
		close(node->pipe[1]);
	if (node->pipe[0])
		close(node->pipe[0]);
	close(shell()->in);
	if (shell()->hdoc)
		unlink(".h_doc_tmp");
	free_na_tree(shell()->root);
	free_linked();
	free_no_env();
	exit(shell()->exit_s);
}

void	cmd_simplao(t_node *node, int key, t_try *bora)
{
	char	**env_cpy;
	char	*path;

	signal_in(SIGINT, SIG_DFL);
	signal_in(SIGQUIT, SIG_DFL);
	env_cpy = shell()->env;
	path = getpath(node->arguments[0]);
	rl_clear_history();
	if (node->pipe[0])
		close(node->pipe[0]);
	handle_redirection(node, key, bora);
	if (node->nodeType == E_BUILT)
		handle_builtin(node, path);
	handle_execution(node, env_cpy, path);
}
