/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 13:04:16 by skavunen          #+#    #+#             */
/*   Updated: 2017/08/08 13:21:43 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void		ft_m_env(t_list *node, char **env)
{
	int		i;

	i = -1;
	if (node)
		while (env[++i])
		{
			ft_putstr(env[i]);
			ft_putchar('\n');
		}
}

void		ft_command(char *cmd, t_list *node, char ***env)
{
	if (!ft_strcmp(cmd, "setenv"))
		ft_m_setenv(node, env);
	else if (!ft_strcmp(cmd, "unsetenv"))
		ft_m_unsetenv(node, *env);
	else if (!ft_strcmp(cmd, "cd"))
		ft_mini_cd(node, env);
	else if (!ft_strcmp(cmd, "env"))
		ft_m_env(node, *env);
}
