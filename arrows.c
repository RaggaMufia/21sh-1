/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:50:50 by skavunen          #+#    #+#             */
/*   Updated: 2017/08/21 18:33:48 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void			ft_left_arrow(t_inp *inp)
{
	if (inp->ind > 0)
	{
		write(1, "\e[D", 3);
		inp->ind--;
	}
}

void			ft_right_arrow(t_inp *inp, char *str)
{
	if (str[inp->ind])
	{
		write(1, "\e[C", 3);
		inp->ind++;
	}
}

void			ft_ctrl_arrow(t_inp *inp)
{
	char		*buf;
	static int	flag;

	buf = ft_strnew(3);
	read(0, buf, 3);
	if (buf[2] == 68)
		ft_ctrl_le(inp);
	if (buf[2] == 67)
		ft_ctrl_ri(inp);
	if (buf[2] == 65 && flag == 0)
		ft_ctrl_up(inp, &flag);
	if (buf[2] == 66 && flag == 1)
		ft_ctrl_do(inp, &flag);
	ft_strdel(&buf);
}

void			ft_arrows(t_cap *cap, t_inp *inp, char **arg)
{
	char		*buf;

	buf = ft_strnew(2);
	read(0, buf, 2);
	if (buf[1] == 65)
		ft_up_arrow(cap, inp, arg);
	else if (buf[1] == 66)
		ft_down_arrow(cap, inp, arg);
	else if (buf[1] == 67)
		ft_right_arrow(inp, *arg);
	else if (buf[1] == 68 && arg)
		ft_left_arrow(inp);
	else
		ft_ctrl_arrow(inp);
	ft_strdel(&buf);
}
