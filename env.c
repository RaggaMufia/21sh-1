/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 14:09:34 by skavunen          #+#    #+#             */
/*   Updated: 2017/06/14 12:57:32 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void		ft_insert_env(char *var, char ***eq)
{
	int		a;
	char	**new;
	char	**env;
	int		i;

	i = 0;
	env = *eq;
	a = -1;
	while (env[i])
		i++;
	new = (char**)malloc(sizeof(char*) * (i + 2));
	i = 0;
	while (env[i])
	{
		new[i] = ft_strdup(env[i]);
		i++;
	}
	new[i] = ft_strdup(new[i - 1]);
	ft_strdel(&new[i - 1]);
	new[i - 1] = ft_strdup(var);
	new[i + 1] = NULL;
	while (env[++a])
		ft_strdel(&env[a]);
	free(env);
	*eq = new;
}

void		ft_rewrite_env(char *var, char **env, int ind)
{
	ft_strdel(&env[ind]);
	env[ind] = ft_strdup(var);
}

void		ft_m_setenv(t_list *list, char ***env)
{
	t_list	*node;
	int		i;
	int		ind;
	char	*str;

	node = list->next;
	while (node)
	{
		str = (char*)node->content;
		i = 0;
		while (str[i] && str[i] != '=')
			i++;
		if (str[i] == '\0')
		{
			node = node->next;
			continue ;
		}
		if ((ind = ft_find_env(*env, str, i)) < 0)
			ft_insert_env(str, env);
		else
			ft_rewrite_env(str, *env, ind);
		node = node->next;
	}
}

void		ft_delete_var(char **env, int ind)
{
	ft_strdel(&env[ind]);
	if (env[ind + 1])
	{
		env[ind] = env[ind + 1];
		while (env[++ind])
			env[ind] = env[ind + 1];
		env[ind] = NULL;
	}
	else
		env[ind] = NULL;
}

void		ft_m_unsetenv(t_list *list, char **env)
{
	t_list	*node;
	int		ind;
	int		a;

	a = -1;
	node = list->next;
	while (node)
	{
		if ((ind = ft_find_env(env, node->content,
		ft_strlen(node->content))) < 0)
			;
		else
			ft_delete_var(env, ind);
		node = node->next;
	}
}
