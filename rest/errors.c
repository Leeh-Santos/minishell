/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:58:31 by learodri          #+#    #+#             */
/*   Updated: 2023/09/18 15:44:43 by learodri@st      ###   ########.fr       */
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

void	display_error(char *str, int x)
{
	perror(str);
	if (!x)
		exit(EXIT_FAILURE);

}
