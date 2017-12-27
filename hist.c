/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 13:32:11 by skavunen          #+#    #+#             */
/*   Updated: 2017/08/23 15:42:17 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_list			*ft_find_hist(int count)
{
	t_list		*node;

	node = g_hist;
	if (node)
	{
		while (count-- > 0 && node)
			node = node->next;
		return (node);
	}
	return (NULL);
}

void			ft_print_har(t_cap *cap, t_inp *inp, char **arg)
{
	if (cap)
		ft_go_home(inp);
	tputs(tgetstr("cd", 0), 1, ft_put);
	ft_bzero(*arg, 1024);
	if (inp->hst)
	{
		inp->ind = ft_strlen(inp->hst);
		write(1, inp->hst, inp->ind);
		*arg = ft_strcat(*arg, inp->hst);
	}
	else
		inp->ind = 0;
	inp->hist = -1;
}

void			ft_print_hist(t_cap *cap, t_inp *inp, t_list *node)
{
	if (cap)
		ft_go_home(inp);
	tputs(tgetstr("cd", 0), 1, ft_put);
	inp->ind = node->content_size - 1;
	write(1, node->content, inp->ind);
}

void			ft_up_arrow(t_cap *cap, t_inp *inp, char **arg)
{
	t_list		*node;

	if ((node = ft_find_hist(++inp->hist)))
	{
		ft_print_hist(cap, inp, node);
		ft_bzero(*arg, 1024);
		*arg = ft_strcat(*arg, node->content);
	}
	else
		inp->hist--;
}

void			ft_down_arrow(t_cap *cap, t_inp *inp, char **arg)
{
	t_list		*node;

	if ((node = ft_find_hist(--inp->hist)))
	{
		ft_print_hist(cap, inp, node);
		ft_bzero(*arg, 1024);
		*arg = ft_strcat(*arg, node->content);
	}
	if (inp->hist < 0)
		ft_print_har(cap, inp, arg);
}
