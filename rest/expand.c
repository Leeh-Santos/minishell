/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimoes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 05:11:49 by msimoes-          #+#    #+#             */
/*   Updated: 2023/09/11 05:11:49 by msimoes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../miniheader.h"

static char *do_expand(char *str, char **env, int i)
{
    //encontrar o nome da var
    //verificar se a var existe
    //encontrar o valor da var
    //substituir os valores 
}

char *expand_check(char *in, char **env)
{
    int i;
    char *ret;

    ret = in;
    i = -1;
    while (ret[++i])
    {
        if (ret[i] == '$' && ret[i + i])
        {
            ret = do_expand(ret, env, i);
            i = -1;
        }
    }
    return ret;
}

//função de apagar quotes