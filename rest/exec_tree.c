/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:30:51 by learodri          #+#    #+#             */
/*   Updated: 2023/09/25 16:44:55 by learodri@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../miniheader.h"

void	wtf_hdoc(t_node *node)
{
	char	*buffer;
	char	*tmp;

	tmp = ft_strdup(node->arguments[0]);
	while (1)
	{
		buffer = readline("> ");
		if (buffer)
		{
			if (ft_strlen(buffer) == ft_strlen(tmp)
				&& !ft_strncmp(tmp, buffer, ft_strlen(node->arguments[0])))
				break ;
			free (buffer);
		}
		else
			break ;
	}
	free (tmp);
	free (buffer);
}

void	redir_error(t_node *node)
{
	ft_putstr_fd("Error: couldn't open file: ", 2);
	ft_putstr_fd(node->arguments[0] , 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void	open_ins(t_node *node)
{
	if (node->nodeType == E_IN)
	{
		if (open(node->arguments[0], O_RDONLY, 0644) == -1)
			redir_error(node);
	}
	else
		wtf_hdoc(node);
}

void	open_outs(t_node *node)
{
	t_node *tmp;
	int fd_tmp;

	tmp = node;
	
	fd_tmp = open(node->arguments[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_tmp == -1)
		redir_error(tmp);
	close (fd_tmp);
		
}

void	which_builtin(t_node *node, int fd)
{
	
	if (!ft_strncmp(node->arguments[0], "echo", 5))
		echo_func(node, fd);
	/*else if (!ft_strncmp(node->arguments[0], "pwd", 4))
		
	else if (!ft_strncmp(node->arguments[0], "env", 4))
		
	else if (!ft_strncmp(node->arguments[0], "cd", 3))
		
	else if (!ft_strncmp(node->arguments[0], "export", 7))
	
	else if (!ft_strncmp(node->arguments[0], "unset", 6))
		
	else if (!ft_strncmp(node->arguments[0], "exit", 5))*/

}

void	simple_built(t_node *root)
{
	t_node *node;
	int	fd;
	int	flag;

	fd = 1;
	flag = 0;
	node = root;
	while (node->left)
	{
		node = node->left;
		if (node->nodeType == E_IN || node->nodeType == E_HDOC)
			open_ins(node);
		if (node->nodeType == E_OUT || node->nodeType == E_APPEND)
		{
			if (!flag)
			{
				if (node->nodeType == E_OUT)
					fd = open(node->arguments[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
				else
					fd = open(node->arguments[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
				if (fd == -1)
					redir_error(node);
				flag++;
			}
			else
				open_outs(node);
		}		
	}
	which_builtin(root, fd);
}

void	papa_process(t_node *node)
{
	if (shell()->nb_cmd != 1)
	{
		if (shell()->in > 0)
			close(shell()->in);
		close(node->pipe[1]);
		shell()->in = node->pipe[0];
	}
	else
	{
		close(node->pipe[0]);
		close(node->pipe[1]);
		if (shell()->in > 0)
			close(shell()->in);
	}
}

void	pipe_it(t_node *sub)
{
	
	if (pipe(sub->pipe) == -1)
	{
		ft_putstr_fd("Error: couldn't open pipe\n", STDERR_FILENO);
		shell()->exit_s = 1;
		exit(shell()->exit_s);
	}
	shell()->pid = fork();
	if (shell()->pid < 0)
	{
		ft_putstr_fd("Error: couldn't create a new process\n", STDERR_FILENO);
		shell()->exit_s = 1;
		exit(shell()->exit_s);
	}
	else if (shell()->pid == 0)
		cmd_simplao(sub, 1);
	papa_process(sub);
}

void	cmd_simplao(t_node *node, int key)
{
	char **env_cpy;
	char *path;

	env_cpy = shell()->env;
	path = getpath(node->arguments[0]);
	rl_clear_history();
	close(node->pipe[0]);
	if (key)
		dale_redir2(node);
	else
		dale_redir(node);
	if (node->nodeType == E_BUILT)
	{
		which_builtin(node, 1);
		exit(shell()->exit_s);
	}
	if (path)
		execve(path, node->arguments, env_cpy);
	free(path);
	close(node->pipe[1]);
	close(node->pipe[0]);
	close(shell()->in);

}

void	nb_cmds(t_node *root)
{
	t_node *tmp;

	tmp = root;
	while (tmp->up)
	{
		shell()->nb_cmd++;
		tmp = tmp->up;
	}
	
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
void	exec_tree(void)
{
	t_node	*root = shell()->root;
	int exit_status;
	
	if (!root)
		return ;
	while (root->left != NULL && root->left->nodeType == E_PIPE)
		root = root->left;
	printf(" chaaama no root poha %d\n", root->nodeType);
	if (!root->up && root->nodeType == E_HDOC)
		return (wtf_hdoc(root));
	if (!root->up && root->nodeType == E_BUILT)
	{
		simple_built(root);
		return (free_na_tree(shell()->root)); // atencao com os free
	}
	if (root->nodeType == E_PIPE)
	{
		shell()->nb_cmd = 3; // com 2 aqui dava hanging depois de executar dois comandos com pipes
		nb_cmds(root);
		pipe_it(root->left);
		shell()->nb_cmd--;
		pipe_it(root->right);
		shell()->nb_cmd--;
		while (root->up)
		{
			root = root->up;
			pipe_it(root->right); // tem que criar aqui fork aqui se nao fecha 
			shell()->nb_cmd--;
		}
		//signal
		wait_process(shell()->pid, shell()->nb_cmd);
		free_na_tree(shell()->root);
		return;
	}
	else
	{
		shell()->pid = fork();
		if (shell()->pid < 0)
			ft_putendl_fd("Error: Fork failed", 2);
		if (shell()->pid == 0)
			cmd_simplao(root, 0);
		waitpid(shell()->pid, &exit_status, 0);
	}

	free_na_tree(shell()->root); 
		
}	