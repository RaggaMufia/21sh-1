/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 12:38:29 by skavunen          #+#    #+#             */
/*   Updated: 2017/08/21 19:05:34 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void			ft_put_hist(char in[], char *str, char **arg)
{
	ft_bzero(*arg, 1024);
	ft_strcat(*arg, str);
	tputs(tgetstr("sr", 0), 1, ft_put);
	tputs(tgetstr("cr", 0), 1, ft_put);
	write(1, "$> ", 3);
	ft_putstr(str);
	tputs(tgetstr("cd", 0), 1, ft_put);
	tputs(tgetstr("sf", 0), 1, ft_put);
	tputs(tgetstr("cr", 0), 1, ft_put);
	write(1, "hist-search: ", 14);
	ft_putstr(in);
}

void			ft_strhist(char in[], t_cap *cap, char **arg, t_inp *inp)
{
	t_list		*list;
	char		*p;
	char		*str;

	list = g_hist;
	p = in;
	if (cap)
		;
	while (list)
	{
		str = list->content;
		if (ft_strstr(str, p))
			break ;
		list = list->next;
	}
	if (list)
		ft_put_hist(in, str, arg);
	else
	{
		ft_bzero(*arg, 1024);
		if (inp->hst)
			ft_strcat(*arg, inp->hst);
	}
}

void			ft_simple_bck(char in[], int *ind)
{
	in[--(*ind)] = '\0';
	write(1, "\e[D", 3);
	tputs(tgetstr("dc", 0), 1, ft_put);
}

void			ft_return_arg(char in[], t_inp *inp, char **arg)
{
	if (in[0] == '\0')
	{
		ft_bzero(*arg, 1024);
		if (inp->hst)
			*arg = ft_strcat(*arg, inp->hst);
	}
	tputs(tgetstr("sr", 0), 1, ft_put);
	tputs(tgetstr("cr", 0), 1, ft_put);
	tputs(tgetstr("cd", 0), 1, ft_put);
	write(1, "$> ", 3);
	ft_putstr(*arg);
	inp->ind = ft_strlen(*arg);
}

void			ft_hist_search(t_cap *cap, t_inp *inp, char **arg)
{
	int			ind;
	char		in[1024];
	char		ch;

	ind = 0;
	ft_bzero(in, 1024);
	write(1, "\nhist-search: ", 14);
	while (1)
	{
		read(0, &ch, 1);
		if (ch == '\n')
			break ;
		else if (KEY(ch))
		{
			if ((ch == 8 || ch == 127) && ind > 0)
				ft_simple_bck(in, &ind);
			continue;
		}
		write(1, &ch, 1);
		in[ind++] = ch;
		ft_strhist(in, cap, arg, inp);
	}
	ft_return_arg(in, inp, arg);
}
