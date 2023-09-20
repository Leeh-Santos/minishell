/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:58:31 by learodri          #+#    #+#             */
/*   Updated: 2023/09/20 16:29:18 by learodri@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../miniheader.h"

void	display_error(char *str, int x) // quando erra cmd tem que forzar 2 vezes para sair com || asdasd >a
{
	perror(str);
	if (!x)
		exit(EXIT_FAILURE);
	

}
