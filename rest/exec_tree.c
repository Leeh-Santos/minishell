/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri <learodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:30:51 by learodri          #+#    #+#             */
/*   Updated: 2023/09/14 22:27:47 by learodri         ###   ########.fr       */
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
		printf("foi - %d\n", fd);//echo_func(node, fd);
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

void	pipe_it(t_node *sub)
{
	int future.in = 0;
	
	if (sub.left != E_PIPE)
	{
		if (pipe(sub->pipe) == -1)
			ft_putendl_fd("Error: Pipe failed", 2);
		shell.out = sub.pipe[1];
		in.shell = sub.pipe[0];//close(sub.pipe[0]); //fecha no righ[0] end no kid
		kid_it(sub.left); // escreve e fecha
		wait();
	}
	if (sub.up)
	{
		// in vem do sub.pipe
		if (pipe(sub->up->pipe) == -1)
			ft_putendl_fd("Error: Pipe failed", 2);
		if (future.in != 0)
			in.shell = future.in;
		out.shell = sub.up.pipe[1]; //escreve e fecha esse end no kid??
		future.in = sub.up.pipe[0];
		kid_it(sub.right);
		wait();
		pipe_it(sub.up);
	}
	else
	{
		if (future.in)
			in.shell = future.in;
		kid_it(sub.right);
		wait();
	}
}

void	exec_tree(void)
{
	t_node	*root = shell()->root;

	
	if (!root)
		return ;

	while (root->left == E_PIPE)
		root = root->left;
	if (!root->up && root->nodeType == E_HDOC)
		return (wtf_hdoc(root));
	if (!root->up && root->nodeType == E_BUILT)
		return (simple_built(root));
	if (root->nodeType == E_PIPE)
		return(pipe_it(root));
	else
		//simple cmd shit

	
		
}	