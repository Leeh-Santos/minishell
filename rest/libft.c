/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: learodri@student.42.fr <learodri>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:12:21 by learodri          #+#    #+#             */
/*   Updated: 2023/09/07 16:29:25 by learodri@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../miniheader.h"

int	ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char    *ft_strcpy(char *s1, char *s2)
{
    int i = 0;
    while (s2[i] != '\0')
    {
        s1[i] = s2[i];
        ++i;
    }
    s1[i] = '\0';
    return (s1);
}

char	*ft_strdup(char *s1)
{
	char	*scpy;
	int		i;
	int		len;

	len = ft_strlen(s1);
	scpy = malloc((len + 1) * sizeof(char));
	if (!scpy)
		return (NULL);
	i = -1;
	while (++i < len)
		scpy[i] = s1[i];
	scpy[i] = 0;
	return (scpy);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	if (!n)
		return (0);
	while (n > 1 && *ptr1 && *ptr2 && (*ptr1 == *ptr2))
	{
		ptr1++;
		ptr2++;
		n--;
	}
	return (*ptr1 - *ptr2);
}

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

