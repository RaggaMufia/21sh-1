/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 15:20:18 by skavunen          #+#    #+#             */
/*   Updated: 2017/08/23 14:02:13 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void			ft_add_hist(char *arg)
{
	t_list		*new;

	new = ft_lstnew(arg, ft_strlen(arg) + 1);
	ft_lstadd(&g_hist, new);
}

void			ft_clear_term(void)
{
	char		*clearterm;
	char		buf[32];
	char		*ap;

	ap = buf;
	clearterm = tgetstr("cl", &ap);
	tputs(clearterm, 1, &ft_put);
}

void			ft_shell(char *arg, char ***env, t_cap *cap)
{
	t_list		*node;
	t_list		*split;
	t_list		*comm;
	t_list		*pipes;
	t_list		*tmp;

	if (arg[0] != '\0')
	{
		node = ft_get_args(&arg, env, cap);
		ft_add_hist(arg);
		comm = ft_node_split(node, ";");
		tmp = comm;
		while (comm)
		{
			split = comm->content;
			pipes = ft_node_split(split, "|");
			ft_exe_pipes(pipes, env);
			ft_del_split(&pipes);
			ft_del_list(&split);
			comm = comm->next;
		}
		ft_del_tmp(&tmp);
		ft_del_list(&node);
	}
	ft_strdel(&arg);
}

void			ft_sig_cont(int sig)
{
	if (sig)
		;
	if (g_inp->arg)
		ft_bzero(g_inp->arg, 1024);
	g_inp->ind = 0;
	g_inp->hist = -1;
	if (g_inp->hst)
		ft_strdel(&g_inp->hst);
	g_inp->hst = ft_strnew(0);
	write(1, "\n$> ", 4);
}

void			ft_21sh(t_cap *cap, char ***env)
{
	char		buf[1024];
	char		*arg;

	tgetent(buf, getenv("TERM"));
	ft_clear_term();
	if (env)
		while (42)
		{
			g_proc = -1;
			signal(SIGINT, ft_sig_cont);
			write(1, "$> ", 3);
			cap->x = 3;
			arg = ft_input(cap);
			if (!ft_strcmp(arg, "exit") || !ft_strcmp(arg, "exit "))
				exit(1);
			ft_putchar('\n');
			tputs(tgetstr("cd", 0), 1, ft_put);
			cap->y++;
			if (ft_check_arg(&arg))
				ft_shell(arg, env, cap);
			else
				ft_strdel(&arg);
		}
}
