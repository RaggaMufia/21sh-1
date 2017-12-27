/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 11:49:25 by skavunen          #+#    #+#             */
/*   Updated: 2017/08/22 18:56:41 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void			ft_child_fd(t_fds *fds, int fl, int fd[])
{
	if (fl == 1)
	{
		dup2(fds->fd[1], 1);
		close(fds->fd[0]);
	}
	close(fd[1]);
	dup2(fd[0], 0);
	if (fds->file > 0 && fl == 0)
		dup2(fds->file, 1);
}

int				ft_new_line(char **str, t_fds *fds)
{
	if ((get_next_line(0, str)) == 0)
	{
		write(1, "\n", 1);
		if (*str)
			ft_strdel(str);
		return (0);
	}
	if (!ft_strcmp(*str, fds->hered))
	{
		if (*str)
			ft_strdel(str);
		return (0);
	}
	return (1);
}

void			ft_here_parent(t_fds *fds, int fd[])
{
	char		*str;
	char		ret[2048];

	close(fd[0]);
	ft_bzero(ret, 2048);
	ft_putstr("heredoc> ");
	while (1)
	{
		if (!ft_new_line(&str, fds))
			break ;
		ft_strcat(ret, str);
		ret[ft_strlen(ret)] = '\n';
		if (str)
			ft_strdel(&str);
		ft_putstr("heredoc> ");
	}
	ft_putstr_fd(ret, fd[1]);
	close(fd[1]);
	ft_strdel(&fds->hered);
	fds->hdoc = -1;
	wait(NULL);
}

void			ft_heredoc(t_fds *fds, char **arg, char **env, int fl)
{
	int			fd[2];
	char		*exe;

	pipe(fd);
	g_proc = fork();
	if (g_proc == 0)
	{
		ft_child_fd(fds, fl, fd);
		exe = ft_findexe(arg[0], env);
		if (exe)
		{
			execve(exe, arg, env);
			ft_strdel(&exe);
		}
		else
			ft_error_cmd(arg[0]);
		if (fds->file > 0)
			close(fds->file);
		close(fd[0]);
		close(fds->fd[1]);
		exit(0);
	}
	else
		ft_here_parent(fds, fd);
}
