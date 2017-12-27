/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backspace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:51:19 by skavunen          #+#    #+#             */
/*   Updated: 2017/08/01 12:56:57 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void		ft_del_char(t_inp *inp, char **arg)
{
	int		i;
	char	*str;

	str = *arg;
	i = inp->ind;
	while (str[i] != '\0')
	{
		str[i] = str[i + 1];
		i++;
	}
}

void		ft_backspace(t_cap *cap, t_inp *inp, char **arg)
{
	char	*del;

	del = tgetstr("dc", 0);
	if (cap && inp && arg)
	{
		if (inp->ind > 0)
		{
			inp->ind--;
			write(1, "\e[D", 3);
			write(1, del, ft_strlen(del));
			ft_del_char(inp, arg);
		}
	}
}
