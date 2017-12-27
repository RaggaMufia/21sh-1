/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 13:11:47 by skavunen          #+#    #+#             */
/*   Updated: 2017/08/22 19:13:50 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void			ft_fdsfile(t_fds *fds, int *flag)
{
	if (fds->file > 0)
		dup2(fds->file, 1);
	if (fds->close != -1)
	{
		if (fds->open != -1)
		{
			if (fds->open == -2)
				close(fds->close);
			else
			{
				dup2(fds->close, fds->open);
				close(fds->open);
				*flag = 1;
			}
		}
	}
	if (fds->in == -3)
		exit(0);
	if (fds->in != 0)
	{
		dup2(fds->in, 0);
		close(fds->in);
	}
}

void			ft_kill(int sig)
{
	if (sig)
		;
	if (g_proc > 0)
	{
		write(1, "\n", 1);
		kill(g_proc, SIGKILL);
	}
}

void			ft_exec_parent(void)
{
	signal(SIGINT, ft_kill);
	waitpid(g_proc, 0, 0);
}

void			ft_exec(char **arg, char **env, t_fds *fds)
{
	char		*exe;
	int			flag;

	pipe(fds->ex);
	g_proc = fork();
	flag = 0;
	if (g_proc == 0)
	{
		exe = ft_findexe(arg[0], env);
		if (exe)
		{
			ft_fdsfile(fds, &flag);
			execve(exe, arg, env);
			ft_strdel(&exe);
			if (fds->file > 0)
				close(fds->file);
			if (flag == 1)
				close(fds->open);
			exit(0);
		}
		else
			ft_error_cmd(arg[0]);
	}
	else
		ft_exec_parent();
}

void			ft_execute(t_list *node, char ***env, t_fds *fds)
{
	char		**arg;

	ft_check_for_file(fds, &node);
	arg = ft_lstochar((t_list*)node->content);
	if (arg[0])
		if (ft_isalpha(arg[0][0]) || ft_isdigit(arg[0][0]))
		{
			ft_set_fds(fds, &arg);
			if (MYCMD(arg[0]) || MYCMD2(arg[0]))
				ft_command(arg[0], (t_list*)node->content, env);
			else if (fds->hdoc == 1)
				ft_heredoc(fds, arg, *env, 0);
			else
				ft_exec(arg, *env, fds);
		}
	ft_del_arg(&arg);
}
