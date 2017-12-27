/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 11:39:34 by skavunen          #+#    #+#             */
/*   Updated: 2017/08/21 17:21:14 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int				ft_fileexist(char *name)
{
	struct stat buf;

	return (lstat(name, &buf) == 0);
}

char			*ft_findpath(char *env, char *cmd)
{
	int			j;
	int			i;
	char		*buf;
	char		*tmp;

	i = 5;
	j = i;
	while (env[++i])
	{
		if (env[i] == ':')
		{
			buf = ft_strsub(env, j, i - j);
			tmp = ft_strjoin(buf, "/");
			ft_strdel(&buf);
			buf = ft_strjoin(tmp, cmd);
			ft_strdel(&tmp);
			j = i + 1;
			if (ft_fileexist(buf))
				return (buf);
			else
				ft_strdel(&buf);
		}
	}
	return (NULL);
}

char			*ft_findexe(char *cmd, char **env)
{
	int			a;
	char		*exe;

	a = ft_find_env(env, "PATH", 4);
	if (a < 0)
		return (NULL);
	exe = ft_findpath(env[a], cmd);
	return (exe);
}
