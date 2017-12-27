/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 15:39:56 by skavunen          #+#    #+#             */
/*   Updated: 2017/08/21 17:20:16 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int				ft_put(int ch)
{
	write(1, &ch, 1);
	return (1);
}

int				ft_find_env(char **env, char *find, int cmp)
{
	int			a;

	a = -1;
	while (env[++a])
		if (strncmp(env[a], find, cmp) == 0 && env[a][cmp] == '=')
			return (a);
	return (-1);
}

int				ft_lst_len(t_list *list)
{
	t_list		*node;
	int			len;

	node = list;
	len = 0;
	while (node)
	{
		len++;
		node = node->next;
	}
	return (len);
}

char			**ft_lstochar(t_list *list)
{
	t_list		*node;
	char		**new;
	int			a;

	a = 0;
	node = list;
	new = (char**)malloc(sizeof(char*) * ft_lst_len(list) + 1);
	while (node)
	{
		new[a++] = ft_strdup(node->content);
		node = node->next;
	}
	new[a] = NULL;
	return (new);
}

void			ft_go_home(t_inp *inp)
{
	int		size;

	size = inp->ind;
	while (size)
	{
		write(1, "\e[D", 3);
		size--;
	}
}
