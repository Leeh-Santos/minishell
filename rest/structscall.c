/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structscall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:19:32 by learodri@st       #+#    #+#             */
/*   Updated: 2023/06/26 16:00:46 by learodri@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../miniheader.h"

t_shell *shell(void)
{
    static t_shell shell;

    return (&shell);
}

