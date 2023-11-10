/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimoes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 02:34:24 by msimoes-          #+#    #+#             */
/*   Updated: 2023/11/09 02:34:24 by msimoes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniheader.h"

void	nb_cmds(t_node *root)
{
	t_node	*tmp;

	tmp = root;
	while (tmp->up)
	{
		shell()->nb_cmd++;
		tmp = tmp->up;
	}
	shell()->nb_cmd_wait = shell()->nb_cmd;
	printf(" numero de comandos -- %d\n", shell()->nb_cmd);
}

void	wait_process(int pid, int num)
{
	int	status;
	int	cmds;

	cmds = num;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell()->exit_s = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		shell()->exit_s = WTERMSIG(status) + 128;
		if (shell()->exit_s == 130)
			ft_putstr_fd("\n", 2);
		else if (shell()->exit_s == 131)
			ft_putendl_fd("Quit (core dumped)", 2);
	}
	while (cmds)
	{
		wait(NULL);
		cmds--;
	}
}

void	exec_pipe(t_node *root, t_try *bora)
{
	shell()->nb_cmd = 2;
	nb_cmds(root);
	pipe_it(root->left, bora);
	shell()->nb_cmd--;
	pipe_it(root->right, bora);
	shell()->nb_cmd--;
	while (root->up)
	{
		root = root->up;
		pipe_it(root->right, bora);
		shell()->nb_cmd--;
	}
	signal_in(SIGINT, SIG_IGN);
	wait_process(bora->pid, shell()->nb_cmd_wait);
}

void	exec_other(t_node *root, t_try *bora)
{
	bora->pid = fork();
	if (bora->pid < 0)
		ft_putendl_fd("Error: Fork failed", 2);
	if (bora->pid == 0)
		cmd_simplao(root, 0, bora);
	signal_in(SIGINT, SIG_IGN);
	wait_process(bora->pid, 1);
}

void	exec_tree(void)
{
	t_node	*root;
	t_try	bora;

	root = shell()->root;
	shell()->in = 0;
	shell()->hdoc = 0;
	if (!root)
		return ;
	while (root->left != NULL && root->left->nodeType == E_PIPE)
		root = root->left;
	printf(" chaaama no root poha, resultados abaixo : %d\n", root->nodeType);
	if (!root->up && root->nodeType == E_HDOC)
		return (wtf_hdoc(root));
	if (!root->up && root->nodeType == E_BUILT)
	{
		simple_built(root);
		return (free_na_tree(shell()->root));
	}
	if (root->nodeType == E_PIPE)
		exec_pipe(root, &bora);
	else
		exec_other(root, &bora);
	free_na_tree(shell()->root);
}


/*void	exec_tree(void)
{
	t_node	*root;
	t_try	bora;

	root = shell()->root;
	shell()->in = 0;
	shell()->hdoc = 0;
	if (!root)
		return ;
	while (root->left != NULL && root->left->nodeType == E_PIPE)
		root = root->left;
	printf(" chaaama no root poha, resultados abaixo : %d\n", root->nodeType);
	if (!root->up && root->nodeType == E_HDOC)
		return (wtf_hdoc(root));
	if (!root->up && root->nodeType == E_BUILT)
	{
		simple_built(root);
		return (free_na_tree(shell()->root));
	}
	if (root->nodeType == E_PIPE)
	{
		shell()->nb_cmd = 2;
		nb_cmds(root);
		pipe_it(root->left, &bora);
		shell()->nb_cmd--;
		pipe_it(root->right, &bora);
		shell()->nb_cmd--;
		while (root->up)
		{
			root = root->up;
			pipe_it(root->right, &bora);
			shell()->nb_cmd--;
		}
		signal_in(SIGINT, SIG_IGN);
		wait_process(bora.pid, shell()->nb_cmd_wait);
		free_na_tree(shell()->root);
		return ;
	}
	else
	{
		bora.pid = fork();
		if (bora.pid < 0)
			ft_putendl_fd("Error: Fork failed", 2);
		if (bora.pid == 0)
			cmd_simplao(root, 0, &bora);
		signal_in(SIGINT, SIG_IGN);
		wait_process(bora.pid, 1);
	}
	free_na_tree(shell()->root);
}
*/