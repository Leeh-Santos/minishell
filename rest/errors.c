/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimoes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:58:31 by learodri          #+#    #+#             */
/*   Updated: 2023/11/07 21:57:56 by msimoes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniheader.h"

// quando erra cmd tem que forzar 2 vezes para sair com || asdasd >a
void	display_error(char *str, int x)
{
	perror(str);
	if (!x)
		exit(EXIT_FAILURE);
}
