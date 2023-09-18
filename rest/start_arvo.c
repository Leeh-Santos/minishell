/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_arvo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 18:50:55 by learodri          #+#    #+#             */
/*   Updated: 2023/09/18 15:29:36 by learodri@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../miniheader.h"


void	print_node_recebido(t_node *node)
{
	t_node *tmp = node;

	int i = 0;
	

	if (node->nodeType >= E_IN && node->nodeType <= E_HDOC)
		printf("nodetype %d - #0 %s - #1 %s\n", tmp->nodeType, tmp->arguments[0], tmp->arguments[1]);
	else if (node->nodeType == E_PIPE)
		printf("PIPE CARAI \n");
	else if (node->nodeType == E_CMD || node->nodeType == E_BUILT)
	{
		printf("nodetype %d", tmp->nodeType);
		while (node->arguments[i])
		{
			printf(" - #%d %s",i , tmp->arguments[i]);
			i++;
		}
		printf("\n");
		
	}
		
}

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

	//print_node_recebido(node);

	if (check_redir_node(node)) 
		where_redir(node);
	else if (check_cmd_node(node)) 
		where_cmd(node);
	else if (check_pipe_node(node))
		add_on_top(node);
	
}


t_token *for_cmd(t_token *start) // contar quantas strs para matriz,
{
	t_token *tmp;
	t_node *new;
	int	nb_str = 0;
	int i = 0;
	
	tmp = start;

	
	while (tmp) //quantas str pa nois maloca
	{
		if (tmp->token[0] == '|')
			break;
		if (tmp->type == 0) // 1 para redir 0 para cmd nao esquece poha
			nb_str++;
		tmp = tmp->next;
	}

	if (!nb_str)   //com NULL nao manda node
		return (NULL);
	
	tmp = start;
	
	new = malloc(sizeof(t_node));
	if (!new || !tmp) //tava tranvando aqui antes tava if (!tmp)
		return NULL;
	new->nodeType = built_ou_cmd(tmp);
	new->left = NULL;
	new->right = NULL;
	new->up = NULL;

	
	new->arguments = malloc(sizeof(char *) * (nb_str + 1)); ///verify here
	if (!new->arguments) //voltar aqui para o final free talbez
	{
		if (new)
			free(new);
		return NULL; 
	}
	
	tmp = start;

	while (tmp)
	{
		if (tmp->token[0] == '|') 
		{
			new->arguments[i] = NULL;
			send_to_tree(new); 
			return(tmp); // pa nois rodar a recursividade dps
		}
		if (tmp->type == 0)
		{
			new->arguments[i] = ft_strdup(tmp->token);
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
	t_node *new;

	tmp = token_node;
	new = malloc(sizeof(t_node));
	
	new->nodeType = redir_tipo(tmp);
	new->arguments = malloc(sizeof(char *) * 2);
	if (!new->arguments || !new)	
		display_error("falha no malloc tree node", 0);
	new->arguments[0] = ft_strdup(arg);
	new->arguments[1] = NULL;  
	new->left = NULL;
	new->right = NULL;
	new->up = NULL;
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
		display_error("deu ruim pipemalloc", 0);
	new->nodeType = E_PIPE;
	new->arguments = NULL;	
	new->left = NULL;
	new->right = NULL;
	new->up = NULL;
	return (new);
	
}

void	token_tree(t_token *head) /*antes que eu esqueca, essa poha vai criando */
{
	t_token	*tmp;
	t_token	*pipe;
	
	
	pipe = NULL;
	tmp = head;
	if (!tmp)
		return ;

	pipe = for_cmd(tmp); 
	for_redir(tmp);

	if (pipe)
	{
		send_to_tree(pipe_node());
		token_tree(pipe->next);
	}
	
}

