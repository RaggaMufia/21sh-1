/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 12:58:03 by skavunen          #+#    #+#             */
/*   Updated: 2017/08/23 14:02:26 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int				ft_check_redirect(char *str)
{
	if (str[0] == '<' && str[1] == '\0')
		return (1);
	return (0);
}

int				ft_check_amper(char *str)
{
	if (ft_isdigit(str[0]) && str[1] == '>' && str[2] == '&')
		return (1);
	return (0);
}

void			ft_file_fds(t_list **list, t_fds *fds, int flag)
{
	t_list		*node;
	char		*str;

	node = *list;
	node = node->next;
	if (node)
	{
		str = (char*)node->content;
		if (flag == 1)
			fds->file = open(str, O_WRONLY | O_CREAT | O_TRUNC,
			S_IWUSR | S_IRUSR);
		if (flag == 2)
			fds->file = open(str, O_WRONLY | O_CREAT | O_APPEND,
			S_IWUSR | S_IRUSR);
	}
}

void			ft_check_for_file(t_fds *fds, t_list **list)
{
	t_list		*check;
	char		*str;
	t_list		*node;
	int			flag;
	t_list		*prev;

	node = *list;
	while (node->next)
		node = node->next;
	check = (t_list*)node->content;
	while (check)
	{
		str = check->content;
		if (!ft_strcmp(str, ">>") || !ft_strcmp(str, ">"))
		{
			flag = (str[1] == '\0' ? 1 : 2);
			ft_file_fds(&check, fds, flag);
			ft_del_list(&check);
			prev->next = NULL;
			return ;
		}
		prev = check;
		check = check->next;
	}
}

int				ft_check_arg(char **arg)
{
	int			i;
	char		*new;
	int			flag;

	flag = 0;
	new = ft_strtrim(*arg);
	i = 0;
	while (new[i])
	{
		if (ft_isalpha(new[i]) || ft_isdigit(new[i]))
		{
			ft_strdel(arg);
			*arg = new;
			return (1);
		}
		i++;
	}
	ft_strdel(&new);
	return (0);
}
