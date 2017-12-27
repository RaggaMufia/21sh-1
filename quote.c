/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 14:57:38 by skavunen          #+#    #+#             */
/*   Updated: 2017/08/22 19:51:07 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static void		ft_put_quote(int flag, t_cap *cap)
{
	if (flag == '\'')
		ft_putstr("quote> ");
	else if (flag == '"')
		ft_putstr("dquote> ");
	else
		ft_putstr("bquote> ");
	cap->x = (flag == '\'' ? 7 : 8);
}

static int		ft_get_quote(char **ar, char *read, int flag)
{
	int			i;
	int			count;
	char		*buf;

	i = 0;
	count = 0;
	while (read[i])
	{
		if (read[i] == flag)
			count++;
		else
		{
			buf = *ar;
			*ar = ft_chjoin(*ar, read[i]);
			ft_strdel(&buf);
		}
		i++;
	}
	return (count);
}

static void		ft_quote(char **str, char **ar, char ch, t_cap *cap)
{
	int			count;
	char		*read;
	char		*tmp;

	count = 1;
	while (count % 2)
	{
		ft_put_quote(ch, cap);
		get_next_line(0, &read);
		tmp = *str;
		*str = ft_strjoin(*str, "\n");
		ft_strdel(&tmp);
		tmp = *str;
		*str = ft_strjoin(*str, read);
		ft_strdel(&tmp);
		tmp = *ar;
		*ar = ft_strjoin(*ar, "\n");
		ft_strdel(&tmp);
		count += ft_get_quote(ar, read, ch);
		ft_strdel(&read);
	}
}

void			ft_is_quote(char **str, int *a, char **ar, t_cap *cap)
{
	char		ch;
	char		*arg;
	int			st;

	st = (*a) + 1;
	arg = *str;
	ch = arg[(*a)];
	while (arg[++(*a)] && arg[(*a)] != ch)
		;
	*ar = ft_strsub(arg, st, (*a) - st);
	if (arg[(*a)] == '\0')
	{
		ft_quote(str, ar, ch, cap);
		--(*a);
	}
}
