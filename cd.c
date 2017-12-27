/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 14:20:50 by skavunen          #+#    #+#             */
/*   Updated: 2017/08/08 14:43:52 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void			ft_set_dir(char *open, char *err)
{
	struct stat	st;

	if (chdir(open) < 0 && chdir(err) < 0)
	{
		if (lstat(open, &st) == 0)
		{
			if (S_ISDIR(st.st_mode))
			{
				ft_putstr("cd: permission denied: ");
				ft_putstr(err);
			}
			else
			{
				ft_putstr("cd: not a directory: ");
				ft_putstr(err);
			}
		}
		else
		{
			ft_putstr("cd: no such file or directory: ");
			ft_putstr(err);
		}
		ft_putchar('\n');
	}
}

char			*ft_create_path(char *dir, char **env)
{
	char		*pwd;
	char		*path;
	char		*buf;
	int			ind;

	if (dir[0] == '~')
	{
		if ((ind = ft_find_env(env, "HOME", 4)) < 0)
			return (NULL);
		buf = ft_strsub(dir, 1, ft_strlen(dir) - 1);
		pwd = ft_strsub(env[ind], 5, ft_strlen(env[ind]) - 5);
		path = ft_strjoin(pwd, buf);
	}
	else
	{
		path = NULL;
		pwd = getcwd(path, 100);
		buf = ft_strjoin(pwd, "/");
		path = ft_strjoin(buf, dir);
	}
	ft_strdel(&pwd);
	ft_strdel(&buf);
	return (path);
}

void			ft_swap_pwd(char ***use, char **env)
{
	int			pw;
	int			old;
	char		*cd;
	char		*od;
	char		*res;

	env = *use;
	if ((pw = ft_find_env(env, "PWD", 3)) < 0 ||
	(old = ft_find_env(env, "OLDPWD", 6)) < 0)
		return ;
	cd = ft_strsub(env[pw], 4, ft_strlen(env[pw]) - 4);
	od = ft_strsub(env[old], 7, ft_strlen(env[old]) - 7);
	chdir(od);
	res = ft_strjoin("PWD=", od);
	ft_strdel(&(env[pw]));
	env[pw] = ft_strdup(res);
	ft_strdel(&res);
	res = ft_strjoin("OLDPWD=", cd);
	ft_strdel(&(env[old]));
	env[old] = ft_strdup(res);
	ft_strdel(&res);
	ft_strdel(&cd);
	ft_strdel(&od);
}

void			ft_update_cd(char ***use, char **env)
{
	char		*cur;
	char		*old;
	int			pw;
	int			od;
	char		*res;

	env = *use;
	if ((pw = ft_find_env(env, "PWD", 3)) < 0 ||
	(od = ft_find_env(env, "OLDPWD", 6)) < 0)
		return ;
	cur = getcwd(NULL, 100);
	old = ft_strsub(env[pw], 4, ft_strlen(env[pw]) - 4);
	res = ft_strjoin("OLDPWD=", old);
	ft_strdel(&env[od]);
	env[od] = ft_strdup(res);
	ft_strdel(&res);
	res = ft_strjoin("PWD=", cur);
	ft_strdel(&env[pw]);
	env[pw] = ft_strdup(res);
	ft_strdel(&res);
	ft_strdel(&cur);
	ft_strdel(&old);
}

void			ft_mini_cd(t_list *list, char ***env)
{
	char		*open;
	char		*cont;

	if (list->next && list->next->next)
		ft_printf("%s %s\n", "cd: string not in pwd:", list->next->content);
	else if (list->next && !ft_strcmp((char*)list->next->content, "-"))
		ft_swap_pwd(env, NULL);
	else
	{
		cont = (list->next ? (char*)list->next->content : "..");
		open = ft_create_path(cont, *env);
		if (open)
		{
			ft_set_dir(open, cont);
			ft_update_cd(env, NULL);
			ft_strdel(&open);
		}
		else
			ft_putstr("Cannot find $HOME\n");
	}
}
