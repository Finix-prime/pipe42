/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmethira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 20:55:29 by vnilprap          #+#    #+#             */
/*   Updated: 2022/08/06 21:09:10 by pmethira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (!dst && !src)
		return (0);
	if (src < dst)
	{
		while (len--)
			*(char *)(dst + len) = *(char *)(src + len);
		return (dst);
	}
	while (i < len)
	{
		*(char *)(dst + i) = *(char *)(src + i);
		i++;
	}
	return (dst);
}

char	*ft_strdup(char const *s1)
{
	char	*ptr;
	size_t	len;

	len = ft_strlen((char *)s1);
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (0);
	ft_memmove(ptr, s1, len);
	ptr[len] = '\0';
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*ptr;

	if (!s2)
		return (ft_strdup(s1));
	if (!s1)
		return (ft_strdup(s2));
	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	ptr = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!ptr)
		return (0);
	ft_memmove(ptr, s1, len1);
	ft_memmove(ptr + len1, s2, len2);
	ptr[len1 + len2] = 0;
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ptr;

	if (!s)
		return (0);
	if (start > ft_strlen((char *)s))
		return (ft_strdup(""));
	if (len + start > ft_strlen((char *)s))
		len = ft_strlen((char *)s) - start;
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (0);
	i = 0;
	ft_memmove(ptr, (char *)(s + start), len);
	ptr[len] = 0;
	return (ptr);
}

void	path_join(char *s1, char *s2, char *dst)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '/';
	i++;
	while (s2[j])
	{
		dst[i] = s2[j];
		i++;
		j++;
	}
	dst[i] = 0;
}
