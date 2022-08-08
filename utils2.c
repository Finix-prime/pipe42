/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmethira <pmethira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 13:57:16 by pmethira          #+#    #+#             */
/*   Updated: 2022/08/08 16:26:35 by pmethira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	error(t_data *pipex, char **cmd)
{
	int		i;

	i = 0;
	pipex->cmd_path = (char *)malloc(100000);
	while (pipex->path[i])
	{
		path_join(pipex->path[i], cmd[0], pipex->cmd_path);
		if (access(pipex->cmd_path, F_OK | X_OK | R_OK) == 0)
			return ;
		i++;
	}
	perror("command not found");
	free(pipex->cmd_path);
	free2(pipex->path);
	free2(pipex->cmd);
	free(pipex->path);
	free(pipex->cmd);
	free(pipex);
	exit(0);
}

char	**free2(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		s++;
	}
	s = 0;
	return (s);
}
