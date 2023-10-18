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

static char *get_name(char *str, int i)
{
    char *ret;
    int j;

    j = 0;
    if (str[i + 1] == '?')
        return ("status");
    while (str[++i] && str[i] != ' ' && str[i] != '\t' \
&& str[i] != '\'' && str[i] != '"' && str[i] != '$')
        j++;
    ret = malloc(sizeof(char) * (j + 1));
    if(!ret)
        return 0;
    ret[j] = 0;
    while (--j > -1)
        ret[j] = str[--i];
    return (ret);
    
}

static char *get_content(char *var_name, char **env, char *str, int x)
{
    int		i;
	int		j;
	char	*content;
	int		len;

	i = -1;
	if (str[x + 1] == '?' && (!ft_strncmp("status", var_name, 7)))
    {
        printf("bateu aqui exit ta como %d\n", shell()->exit_s);
		return (ft_itoa(shell()->exit_s));
    }
	while (env[++i] && !verify_var(var_name, env[i]))
		;
	len = -1;
	while (env[i] && env[i][++len] && env[i][len] != '=')
		;
	len += (env[i] && env[i][len] == '=');
	content = malloc(sizeof(char) * (ft_strlen(env[i]) * len) + 1);
	if (!content)
		return 0;
	j = 0;
	while (env[i] && env[i][len - 1])
		content[j++] = env[i][len++];
	content[j] = '\0';
	free (var_name);
	return (content);
}

char *replace_var(char *str, char *var_content, int x)
{
    int		i;
	int		j;
	int		k;
	char	*ret;

    
	ret = malloc(sizeof(char) * (expander_len(str) + ft_strlen(var_content) + 1));
	if (!ret)
		return 0;
	i = -1;
	k = -1;
	j = -1;
	while (str[++i] && (str[i] != '$' || i < x))
		ret[++k] = str[i];
	while (var_content[++j])
		ret[++k] = var_content[j];
	while (str[++i] && str[i] != ' ' && str[i] != '\t' && str[i] \
	!= '"' && str[i] != '\'' && str[i] != '$' && env_char(str[i]))
		;
	while (str[i])
		ret[++k] = str[i++];
	ret[++k] = 0;
	return (ret);
}

static char *do_expand(char *str, char **env, int i)
{
    char *var_name;
    char *var_content;
    char *ret;

    var_name = get_name(str, i);     //encontrar o nome da var
    var_content = get_content(var_name, env, str, i);     //encontrar o valor da var
    if(!var_content)
        return 0;
    ret = replace_var(str, var_content, i);     //substituir a var pelo valor
    free(var_content);
    free(str);
    return (ret);
}

char	*del_quotes(char *str)
{
    int i;
    int j;
    char *ret;
    

    i = -1;
    j = 0;
    while(str[++i])
        if(str[i] == '\'' || str[i] == '\"')
            j++;
    if (j == 0)
        return (str);
    ret = malloc(sizeof(char) * ((ft_strlen(str) - j) + 1));
    if(!ret)
        return 0;
    i = -1;
    j = -1;
    while (str[++i])
    {
        if (str[i] != '\'' && str[i] != '\"')
            ret[++j] = str[i];
    }
    ret[++j] = 0;
    free(str);
    return (ret);
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
        if ((ret[i] == '$' && ret[i + 1]) && c != '\'')
        {
            ret = do_expand(ret, env, i);
            i = -1;
            c = 0;
        }
    }
    //ret = del_quotes(ret);
    return (ret);
}

