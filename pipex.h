/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmethira <pmethira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:33:50 by pmethira          #+#    #+#             */
/*   Updated: 2022/07/30 15:35:32 by pmethira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_data
{
	char	**path;
	char	**cmd;
	char	*cmd_path;
	char	**av;
	char	*ev;
	int		ac;
	int		end[2];
	int		fdin;
	int		fdout;
	int		av_index;
}	t_data;

char	*get_next_line(int fd);
char	*ft_strdup(char const *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlen(char const *s);
int		execve(const char *pathname, char *const argv[], char *const envp[]);
int		access(const char *pathname, int mode);
int		wd_count(char const *s, char c);
int		al_count(char *str, char c);
void	word_add(char *str, char c, char *list);
void	reserve_word(char const *s, char c, char **list);
char	**split(char const *s, char c);
int		ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin_pipe(char const *s1, char const *s2);
char	*get_next_line(int fd);
void	freeall(t_data *pipex);

#endif
