/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 15:41:56 by skavunen          #+#    #+#             */
/*   Updated: 2017/08/22 19:54:15 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void			ft_add_char(char **arg, char ch, t_inp *inp)
{
	int			ind;
	char		*str;
	char		buf;
	char		next;

	str = *arg;
	ind = inp->ind;
	buf = str[ind];
	str[ind] = ch;
	while (str[++ind] != '\0')
	{
		next = str[ind];
		str[ind] = buf;
		buf = next;
	}
	str[ind] = buf;
	inp->ind++;
	tputs(tgetstr("im", 0), 1, ft_put);
	tputs(tgetstr("ic", 0), 1, ft_put);
	write(1, &ch, 1);
	tputs(tgetstr("ei", 0), 1, ft_put);
	if (inp->hst)
		ft_strdel(&inp->hst);
	inp->hst = ft_strdup(*arg);
}

void			ft_keys(char ch, t_cap *cap, t_inp *inp, char **arg)
{
	if (ch == 8 || ch == 127)
		ft_backspace(cap, inp, arg);
	else if (ch == 27)
		ft_arrows(cap, inp, arg);
	else if (ch == 18)
		ft_hist_search(cap, inp, arg);
	else if (ch == 9)
		ft_tab(cap, inp, arg);
	else if (ch == 11 || ch == 12)
		ft_home_end(ch, inp);
}

void			ft_del_inp(t_inp **inp)
{
	t_inp		*del;

	del = *inp;
	if (del->hst)
		ft_strdel(&del->hst);
	if (del->cpl)
		ft_del_list(&del->cpl);
	ft_memdel((void**)&del);
}

void			ft_sigquit(t_inp *inp)
{
	if (!ft_strlen(inp->arg))
		exit(1);
}

char			*ft_input(t_cap *cap)
{
	char		ch;
	char		*arg;

	g_inp = ft_init_inp();
	arg = g_inp->arg;
	ft_bzero(arg, 1024);
	tcsetattr(0, TCSANOW, &g_new);
	signal(SIGINT, ft_sig_cont);
	while (42)
	{
		read(0, &ch, 1);
		if (ch == '\n')
			break ;
		else if (ch == 4)
			ft_sigquit(g_inp);
		else if (KEY(ch) || KEY2(ch))
			ft_keys(ch, cap, g_inp, &arg);
		else
			ft_add_char(&arg, ch, g_inp);
		if (ch != 9)
			ft_reset_tab(g_inp);
	}
	ft_del_inp(&g_inp);
	tcsetattr(0, TCSANOW, &g_old);
	return (arg);
}
