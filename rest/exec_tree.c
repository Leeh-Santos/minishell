/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:30:51 by learodri          #+#    #+#             */
/*   Updated: 2023/10/17 17:26:05 by learodri@st      ###   ########.fr       */
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
	shell()->exit_s = 1;
	exit(shell()->exit_s);
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
	else if (!ft_strncmp(node->arguments[0], "pwd", 4))
		pwd_func(fd);
	else if (!ft_strncmp(node->arguments[0], "cd", 3))
		cd_func(node->arguments, shell()->env);
	else if (!ft_strncmp(node->arguments[0], "env", 4))
		env_print(shell()->env, fd);
	else if (!ft_strncmp(node->arguments[0], "exit", 5))
		exit_it(node->arguments, shell()->env);
	else if (!ft_strncmp(node->arguments[0], "export", 7))
		export_it(node->arguments, shell()->env, fd);
	else if (!ft_strncmp(node->arguments[0], "unset", 6))
		unset_it(node->arguments, shell()->env);
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

void	pipe_it(t_node *sub, t_try *bora)
{
	
	if (pipe(sub->pipe) == -1)
	{
		ft_putstr_fd("Error: couldn't open pipe\n", STDERR_FILENO);
		shell()->exit_s = 1;
		exit(shell()->exit_s);
	}
	bora->pid = fork();
	if (bora->pid < 0)
	{
		ft_putstr_fd("Error: couldn't create a new process\n", STDERR_FILENO);
		shell()->exit_s = 1;
		exit(shell()->exit_s);
	}
	else if (bora->pid == 0)
		cmd_simplao(sub, 1, bora);
	papa_process(sub);
}

void	cmd_simplao(t_node *node, int key, t_try *bora)
{
	char **env_cpy;
	char *path;

	signal_in(SIGINT, SIG_DFL);
	signal_in(SIGQUIT, SIG_DFL);
	env_cpy = shell()->env;
	path = getpath(node->arguments[0]);
	rl_clear_history();
	if (node->pipe[0])
		close(node->pipe[0]);
	if (key)
		dale_redir2(node, bora);
	else
		dale_redir(node);
	if (node->nodeType == E_BUILT)
	{
		which_builtin(node, 1);
		shell()->exit_s = 0;
		exit(shell()->exit_s);
	}
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
	printf("\n trocou o exit : %d \n", shell()->exit_s);
	free_na_tree(shell()->root); // add aqui em caso de single arg errado ex : lls dava leak	 
	exit(shell()->exit_s); // para only redir nodes
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
void	exec_tree(void)
{
	t_node	*root = shell()->root;
	//int exit_status;
	shell()->in = 0; // para limpar fd se nao da merda no proximo uso dos pipes
	shell()->hdoc = 0;
	t_try bora;
	
	
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
		return (free_na_tree(shell()->root)); // atencao com os free
	}
	if (root->nodeType == E_PIPE)
	{
		shell()->nb_cmd = 2; // com 2 aqui dava hanging depois de executar dois comandos com pipes
		nb_cmds(root);
		pipe_it(root->left, &bora);
		shell()->nb_cmd--;
		pipe_it(root->right, &bora);
		shell()->nb_cmd--;
		while (root->up)
		{
			root = root->up;
			pipe_it(root->right, &bora); // tem que criar aqui fork aqui se nao fecha 
			shell()->nb_cmd--;
		}
		signal_in(SIGINT, SIG_IGN);
		wait_process(bora.pid, shell()->nb_cmd_wait); //INICIAAAAAAAAAAAAAAAAAAR AQUI COM O NUMERO DE CMDS CARALHO
		free_na_tree(shell()->root);
		return;
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
		printf("deu ruim no cdm exit como %d\n", shell()->exit_s);
	}

	free_na_tree(shell()->root); 
		
}	