/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 14:09:47 by skavunen          #+#    #+#             */
/*   Updated: 2017/08/22 19:54:11 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_term				ft_init_term(void)
{
	t_term			term;

	tcgetattr(STDIN_FILENO, &term);
	g_new = term;
	g_new.c_lflag &= ~ICANON & ~ECHO;
	g_new.c_cc[VMIN] = 1;
	g_new.c_cc[VTIME] = 0;
	return (term);
}

char				**ft_init_env(char **env)
{
	char			**new;
	int				a;

	a = 0;
	while (env[a])
		a++;
	new = (char**)malloc(sizeof(char*) * (a + 1));
	a = -1;
	while (env[++a])
		new[a] = ft_strdup(env[a]);
	new[a] = NULL;
	return (new);
}

t_cap				*ft_init_cap(void)
{
	t_cap			*new;
	char			buf[32];
	char			*ap;
	char			buf2[1024];

	ap = buf;
	tgetent(buf2, getenv("TERM"));
	new = (t_cap*)malloc(sizeof(t_cap));
	new->tgo = ft_strdup(tgetstr("cm", &ap));
	new->left = ft_strdup(tgetstr("le", &ap));
	new->deline = ft_strdup(tgetstr("cd", &ap));
	new->x = 0;
	new->y = 0;
	new->mx = tgetnum("co");
	new->my = tgetnum("li");
	return (new);
}

t_inp				*ft_init_inp(void)
{
	t_inp			*new;

	new = (t_inp*)malloc(sizeof(t_inp));
	new->ind = 0;
	new->hist = -1;
	new->arg = NULL;
	new->hst = NULL;
	new->cpl = NULL;
	new->cplind = -1;
	new->arg = ft_strnew(1024);
	return (new);
}

t_fds				*ft_init_fds(void)
{
	t_fds			*new;

	new = (t_fds*)malloc(sizeof(t_fds));
	new->in = 0;
	new->close = -1;
	new->open = -1;
	new->file = -1;
	new->hdoc = -1;
	new->hered = NULL;
	new->mem1 = dup(1);
	new->mem2 = dup(0);
	new->mem3 = dup(2);
	return (new);
}
