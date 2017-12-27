/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:51:38 by skavunen          #+#    #+#             */
/*   Updated: 2017/08/22 18:42:10 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void			ft_find_in_dir(t_inp *inp, char *find, int len)
{
	DIR			*d;
	t_dirent	*dir;

	d = opendir(".");
	while ((dir = readdir(d)))
		if (!ft_strncmp(dir->d_name, find, len))
			ft_lstpushback(&inp->cpl, dir->d_name,
			ft_strlen(dir->d_name) + 1);
	closedir(d);
	inp->cplen = len;
}

void			ft_del_prev(t_inp *inp, char **arg)
{
	int i;
	int dl;

	if (arg)
		;
	dl = inp->cplprev;
	i = inp->ind;
	while (dl-- >= 0)
		inp->arg[i--] = 0;
	dl = inp->cplprev;
	while (dl--)
	{
		write(1, "\e[D", 3);
		tputs(tgetstr("dc", 0), 1, ft_put);
	}
	inp->ind -= inp->cplprev;
}

void			ft_write_compl(t_inp *inp, t_cap *cap)
{
	t_list		*node;

	if (cap)
		;
	if (inp->cpl)
	{
		node = inp->cpl;
		tputs(tgetstr("sc", 0), 1, ft_put);
		tputs(tgetstr("do", 0), 1, ft_put);
		tputs(tgetstr("cr", 0), 1, ft_put);
		while (node)
		{
			write(1, node->content, node->content_size - 1);
			tputs(tgetstr("ta", 0), 1, ft_put);
			node = node->next;
		}
		inp->cplind = 0;
		tputs(tgetstr("rc", 0), 1, ft_put);
	}
}

void			ft_next_cpl(t_inp *inp, char **arg)
{
	int			ind;
	t_list		*node;
	int			len;

	len = inp->cplen;
	node = inp->cpl;
	ind = inp->cplind;
	while (ind--)
		node = node->next;
	if (!node)
	{
		node = inp->cpl;
		ft_del_prev(inp, arg);
		inp->cplind = 0;
	}
	if (inp->cplind)
		ft_del_prev(inp, arg);
	inp->cplprev = ft_strlen((char*)node->content + len);
	ft_putstr((char*)node->content + len);
	(void)ft_strcat(*arg, node->content + len);
	inp->ind += inp->cplprev;
	inp->cplind++;
}

void			ft_tab(t_cap *cap, t_inp *inp, char **arg)
{
	int			ind;
	char		*str;
	char		*find;

	ind = inp->ind;
	str = *arg;
	if (inp->cplind != -1)
	{
		ft_next_cpl(inp, arg);
		return ;
	}
	if (!ind)
		return ;
	while (ft_isalpha(str[--ind]))
		;
	ind++;
	find = ft_strsub(str, ind, inp->ind - ind);
	if (find)
	{
		ft_find_in_dir(inp, find, ft_strlen(find));
		ft_write_compl(inp, cap);
	}
	ft_strdel(&find);
}
