/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmethira <pmethira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:45:51 by pmethira          #+#    #+#             */
/*   Updated: 2022/08/01 14:17:08 by pmethira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_atoi(const char *str)
{
	int				i;
	int				pre;
	long long int	ans;

	i = 0;
	pre = 1;
	ans = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			pre = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		ans = ans * 10 + (str[i] - '0');
		i++;
	}
	return (pre * ans);
}

char	*ft_strjoin_pipe(char const *s1, char const *s2)
{
	char	*s3;
	int		i;
	int		j;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	s3 = malloc(sizeof(char) * (i + j + 1));
	if (!s3)
		return (0);
	while (*s1)
	{
		*s3 = *s1;
		s3++;
		s1++;
	}
	while (*s2)
	{
		*s3 = *s2;
		s3++;
		s2++;
	}
	*s3 = '\0';
	return (s3 - i - j);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (ft_strlen(s1) > ft_strlen(s2))
			len = ft_strlen(s2);
	else
		len = ft_strlen(s1);
	while (i <= len && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
