/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_arvo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 18:50:55 by learodri          #+#    #+#             */
/*   Updated: 2023/08/30 12:58:52 by learodri@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../miniheader.h"

static int	built_ou_cmd(t_token *node)
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

	while(tmp)
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

void	send_to_tree(t_node *node)
{
	t_node *tmp = node;
	printf("treenodetype %d - 1str %s - 2str %s \n", tmp->nodeType, tmp->arguments[0], tmp->arguments[1]);
	
}


t_token *for_cmd(t_token *start) // contar quantas strs para matriz, ja manda pra arvore, fodase, nao precisa devolver o t_
{
	t_token *tmp;
	t_node *new;
	int	nb_str;
	int i = 0;
	
	tmp = start;
	new = malloc(sizeof(t_node));
	if (!new || !tmp)
		return NULL;
	new->nodeType = built_ou_cmd(tmp);
	new->left = NULL;
	new->right = NULL;
	new->up = NULL;

	while (tmp)
	{
		if (tmp->type == 0)
			nb_str++;
		tmp = tmp->next;
	}

	new->arguments = malloc(sizeof(char *) * (nb_str + 1)); ///verify here
	if (!new->arguments) //voltar aqui para o final free talbez
	{
		if (new)
			free(new);
		return NULL; 
	}
	new->pipe[0] = -1;
	new->pipe[1] = -1;
	tmp = start;

	while (tmp)
	{
		if (tmp->token[0] == '|')
		{
			new->arguments[i] = NULL;
			send_to_tree(new); 
			return(tmp);
		}
		if (tmp->type == 0)
		{
			new->arguments[i] = ft_strdup(tmp->token);
			if (!new->arguments[i])
			display_error("deu ruim na mtx node-arvore", 0);
			i++;
		}
		tmp = tmp->next;
	}

	new->arguments[i] = NULL;
	send_to_tree(new);

	return NULL; // em caso de nao ter mais pipes ou nao ter
	
}

static int redir_tipo(t_token *redir)
{
	t_token *tmp;

	tmp = redir;

	
	if (tmp->token[0] == '<' && tmp->token[1] == '<')
		return (E_HDOC);
	else if (tmp->token[0] == '>' && tmp->token[1] == '>')
		return (E_APPEND);
	else if (tmp->token[0] == '<' && !tmp->token[1])
		return (E_IN);
	else if (tmp->token[0] == '>' && !tmp->token[1])
		return (E_OUT);
	else
		return (-1);
	
}

t_node*	redir_node(t_token *token_node, char *arg)
{
	t_token *tmp;

	tmp = token_node;
	t_node *new = malloc(sizeof(t_node));
	
	new->nodeType = redir_tipo(tmp);
	new->arguments = malloc(sizeof(char *) * 2);
	if (!new->arguments || !new)	
		display_error("falha no malloc tree node", 0);
	new->arguments[0] = ft_strdup(arg);
	new->arguments[1] = '\0';
	new->left = NULL;
	new->right = NULL;
	new->up = NULL;
	new->pipe[0] = -1;
	new->pipe[1] = -1;
	
	return (new);
}

void	for_redir(t_token *start) // ja manda o tipo do redir, o parsing que q ta ok! se nao da ruim
{
	t_token	*tmp;
		
	tmp = start;

	while (tmp)
	{
		if (tmp->token[0] == '|')
			return;
		if (tmp->type == 1)
		{
			send_to_tree(redir_node(tmp, tmp->next->token));
			tmp = tmp->next->next; // > arg
			continue;
		}
		tmp = tmp->next;
	}
	
}

t_node *pipe_node(void)
{

	t_node *new;

	new = malloc(sizeof(t_node));
	if (!new)
		return NULL;
	new->nodeType = E_PIPE;
	new->arguments = NULL;	
	new->left = NULL;
	new->right = NULL;
	new->up = NULL;
	new->pipe[0] = -1;
	new->pipe[1] = -1;

	return (new);
	
}

t_node *token_tree(t_token *head)
{
	t_token	*tmp;
	t_token	*pipe;
	
	pipe = NULL;
	tmp = head;
	if (!tmp)
		return NULL;

	pipe = for_cmd(tmp); //manda node para arvore
	for_redir(tmp); // manda node para arover

	if (pipe)
	{
		send_to_tree(pipe_node());
		token_tree(pipe);
	}
	return (shell()->root);
}


/*
{
    E_CMD,
    E_PIPE,
    E_IN,
    E_OUT,
    E_APPEND,
    E_HDOC,
    E_BUILT
} t_type;*/

