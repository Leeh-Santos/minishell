/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimoes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 03:01:29 by msimoes-          #+#    #+#             */
/*   Updated: 2023/11/09 03:01:29 by msimoes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniheader.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	index;

	if (!s)
		return ;
	index = 0;
	while (s[index] != '\0')
	{
		ft_putchar_fd(s[index], fd);
		index++;
	}
}

void	ft_putendl_fd(char *s, int fd)
{
	int	index;

	index = 0;
	if (!s)
		return ;
	while (s[index] != '\0')
	{
		ft_putchar_fd(s[index], fd);
		index++;
	}
	ft_putchar_fd('\n', fd);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*snew;
	size_t	n1;
	size_t	n2;
	size_t	slen;

	if (!s1 || !s2)
		return (NULL);
	slen = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	snew = (char *)malloc(sizeof(char) * (slen + 1));
	n1 = 0;
	n2 = 0;
	if (snew == NULL)
		return (NULL);
	while (s1[n1] != '\0')
	{
		snew[n1] = s1[n1];
		n1++;
	}
	while (s2[n2] != '\0')
	{
		snew[n1 + n2] = s2[n2];
		n2++;
	}
	snew[n1 + n2] = '\0';
	return (snew);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!(*needle))
		return ((char *)haystack);
	i = 0;
	while (haystack[i] && len && i < len)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && (i + j) < len)
		{
			j++;
			if (!needle[j])
				return ((char *)&haystack[i]);
		}
		i++;
	}
	return (NULL);
}
