/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmethira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 19:01:30 by pmethira          #+#    #+#             */
/*   Updated: 2022/08/04 14:12:39 by pmethira         ###   ########.fr       */
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
	perror(cmd[0]);
	free(pipex->cmd_path);
	pipex->cmd_path = 0;
}

void	forking(t_data *pipex, char **envp)
{
	int		id;

	if (pipe(pipex->end) == -1)
		return ;
	id = fork();
	if (id == 0)
	{
		close(pipex->end[0]);
		if (pipex->av_index == pipex->ac - 2)
			dup2(pipex->fdout, 1);
		else
			dup2(pipex->end[1], 1);
		execve(pipex->cmd_path, pipex->cmd, envp);
	}
	else
	{
		wait(0);
		close(pipex->end[1]);
		dup2(pipex->end[0], 0);
	}
	return ;
}

void	piping(t_data *pipex, char **envp)
{
	int	i;

	i = 0;
	while (pipex->av_index <= pipex->ac - 2)
	{
		pipex->cmd = split(pipex->av[pipex->av_index], ' ');
		error(pipex, pipex->cmd);
		forking(pipex, envp);
		while (pipex->cmd[i])
		{
			free(pipex->cmd[i]);
			i++;
		}
		free(pipex->cmd);
		pipex->cmd = 0;
		free(pipex->cmd_path);
		pipex->cmd_path = 0;
		pipex->av_index++;
	}
}

void	here(t_data *pipex)
{
	char	*buff;

	if (!ft_strncmp("here_doc", pipex->av[1], 7))
	{
		pipex->av_index = 3;
		pipex->fdout = open(pipex->av[pipex->ac - 1], \
			O_WRONLY | O_CREAT | O_APPEND, 0644);
		pipex->fdin = open("log", O_CREAT | O_RDWR, 0777);
		while (1)
		{
			buff = get_next_line(0);
			if (ft_strncmp(buff, pipex->av[2], ft_strlen(pipex->av[2])) == 0)
				break ;
			write(pipex->fdin, buff, ft_strlen(buff));
		}
		dup2(pipex->fdin, 0);
	}
	else
	{
		pipex->fdout = open(pipex->av[pipex->ac - 1], \
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(pipex->fdin, 0);
	}
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*pipex;
	int		i;

	if (argc < 5)
	{
		perror("argument error");
		return (0);
	}
	pipex = (t_data *)malloc(sizeof(t_data));
	pipex->ac = argc;
	i = 0;
	while (ft_strncmp("PATH", envp[i], 4))
		i++;
	pipex->av = argv;
	pipex->ev = envp[i] + 5;
	pipex->path = split(pipex->ev, ':');
	pipex->av_index = 2;
	if (ft_strncmp("here_doc", pipex->av[1], 7))
		pipex->fdin = open(argv[1], O_RDONLY);
	here(pipex);
	piping(pipex, envp);
	i = 0;
	while (pipex->path[i])
	{
		free(pipex->path[i]);
		i++;
	}
	free(pipex->path);
	free(pipex->cmd_path);
	free(pipex);
	return (0);
}
