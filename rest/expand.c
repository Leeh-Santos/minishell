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
    char *var_name;
    char *var_content;
    char *ret;

    var_name = get_name(str, i);     //encontrar o nome da var
    var_content = get_content(var_name, env, str, i);     //encontrar o valor da var
    if(!value)
        return 0;
    ret = replace_var(str, var_content, i);     //substituir a var pelo valor
}

char *expand_check(char *in, char **env)
{
    int i;
    char c;
    char *ret;

    ret = in;
    i = -1;
    c = 0;
    while (ret[++i])
    {
        if((ret[i] == '\'' || ret[i] == '\"'))
        {
            if(!c)
                c = ret[i];
            else if(c == ret[i])
                c = 0;
        }
        if ((ret[i] == '$' && ret[i + i]) && c == '\"')
        {
            ret = do_expand(ret, env, i);
            i = -1;
            c = 0;
        }
    }

    return ret;
}

