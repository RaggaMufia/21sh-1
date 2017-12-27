/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrlarr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 18:20:18 by skavunen          #+#    #+#             */
/*   Updated: 2017/08/21 18:31:23 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void			ft_ctrl_up(t_inp *inp, int *flag)
{
	if (((int)ft_strlen(inp->arg) + 3) > tgetnum("co"))
	{
		tputs(tgetstr("up", 0), 1, ft_put);
		inp->ind -= tgetnum("co");
		*flag = 1;
	}
}

void			ft_ctrl_do(t_inp *inp, int *flag)
{
	int			width;

	if (((int)ft_strlen(inp->arg) + 3) > tgetnum("co"))
	{
		tputs(tgetstr("do", 0), 1, ft_put);
		width = inp->ind + 3;
		while (width--)
			write(1, "\e[C", 3);
		inp->ind += tgetnum("co");
		*flag = 0;
	}
}

void			ft_ctrl_le(t_inp *inp)
{
	int			i;
	int			j;

	if (inp->ind > 0)
	{
		i = inp->ind - 1;
		j = inp->ind;
		while (inp->arg[i] == ' ')
			i--;
		while (i >= 0 && inp->arg[i] != ' ')
			i--;
		inp->ind = i + 1;
		while (++i < j)
			write(1, "\e[D", 3);
	}
}

void			ft_ctrl_ri(t_inp *inp)
{
	int			i;
	int			j;

	if (inp->arg[inp->ind])
	{
		i = inp->ind;
		j = i;
		while (inp->arg[i] && inp->arg[i] != ' ')
			i++;
		while (inp->arg[i] && inp->arg[i] == ' ')
			i++;
		inp->ind = i;
		while (i-- > j)
			write(1, "\e[C", 3);
	}
}
