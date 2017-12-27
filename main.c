/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 14:26:22 by skavunen          #+#    #+#             */
/*   Updated: 2017/08/22 15:21:23 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int					main(int ac, char **av, char **env)
{
	char			**nenv;
	t_cap			*cap;

	g_hist = NULL;
	cap = ft_init_cap();
	if (ac != 0 && av)
		g_old = ft_init_term();
	nenv = ft_init_env(env);
	ft_21sh(cap, &nenv);
	tcsetattr(0, TCSANOW, &g_old);
	exit(1);
}
