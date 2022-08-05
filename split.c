/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmethira <pmethira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:57:28 by pmethira          #+#    #+#             */
/*   Updated: 2022/08/05 16:01:49 by pmethira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	wd_count(char const *s, char c)
{
	char	*str;
	int		word;

	str = (char *)s;
	word = 0;
	while (*str)
	{
		while (*str == c)
			str++;
		while (*str != c && *str)
			str++;
		if ((*str == 0 && *(str - 1) != c) || *str == c)
			word++;
	}
	return (word);
}

int	al_count(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i] != c && str[i])
	{
		i++;
	}
	return (i);
}

void	word_add(char *str, char c, char *list)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i])
	{
		list[i] = str[i];
		i++;
	}
	list[i] = 0;
}

void	reserve_word(char const *s, char c, char **list)
{
	char	*str;
	int		i;
	int		j;

	str = (char *)s;
	i = 0;
	j = 0;
	while (*str && j < wd_count(s, c))
	{
		while (*str == c)
			str++;
		i = al_count(str, c);
		list[j] = (char *)malloc(sizeof(char) * (i + 1));
		if (!list[j])
		{
			i = 0;
			while (list[i])
				free(list[i++]);
			free(list);
			return ;
		}
		word_add(str, c, list[j]);
		while (*str != c && *str)
			str++;
		j++;
	}
	list[j] = 0 ;
}

char	**split(char const *s, char c)
{
	char	**list;
	int		word;

	word = wd_count(s, c);
	list = (char **)malloc(sizeof(char *) * (word + 1));
	if (!list)
		return (0);
	reserve_word(s, c, list);
	return (list);
}
