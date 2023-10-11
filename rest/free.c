/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimoes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:13:43 by learodri@st       #+#    #+#             */
/*   Updated: 2023/10/11 21:58:56 by msimoes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../miniheader.h"

void	free_na_tree(t_node *root)
{
	int	i;

	i = 0;

	if (!root)
		return;
	free_na_tree(root->left);
	free_na_tree(root->right);

	if (root->arguments)
	{
		while (root->arguments[i])
		{
			free(root->arguments[i]);
			i++;
		}
		free(root->arguments);
	}
	printf("node deletado %d\n", root->nodeType);
	free(root);
	
}

void	free_linked()
{
	t_token *tmp;
	t_token	*current;

	current = shell()->head;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		free(tmp->token);
		free(tmp);
	}
	shell()->head =	NULL;

}

void	free_split(char **args)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	while (args[size])
		size++;
	while (i < size)
		free(args[i++]);
	free(args);
}
