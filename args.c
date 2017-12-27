/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 15:20:37 by skavunen          #+#    #+#             */
/*   Updated: 2017/08/22 19:44:55 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void			ft_args_smpl(char *arg, int *i, char **str)
{
	int			a;

	a = *i;
	while (arg[a] && (arg[a] == ' ' || arg[a] == '\t'))
		a++;
	*i = a;
	while (ARGWL(arg[a]) && arg[a] != '\'' && arg[a] != '"')
		a++;
	*str = ft_strsub(arg, *i, a - *i);
	if (arg[a] == ';' || arg[a] == '|' || QUOTE(arg[a]) || arg[a] == '|' ||
		arg[a] == '>' || arg[a] == '<')
		--a;
	*i = a;
}

void			ft_env_var(char *arg, int *a, char **ar, char **env)
{
	char		*var;
	int			ind;
	int			find;
	int			cmp;

	ind = *a;
	while (ft_isalpha(arg[++ind]) || ft_isdigit(arg[ind]))
		;
	var = ft_strsub(arg, *a + 1, ind - *a);
	*a = ind + 1;
	cmp = ft_strlen(var);
	if ((find = ft_find_env(env, var, cmp)) < 0)
		*ar = ft_strnew(0);
	else
		*ar = ft_strsub(env[find], cmp + 1, ft_strlen(env[find]) - cmp - 1);
	ft_strdel(&var);
}

void			ft_spec_var(char *str, int *i, char **ar)
{
	char		ch;
	int			count;
	char		*new;

	ch = str[(*i)];
	count = 0;
	while (str[(*i)] == ch)
	{
		count++;
		(*i)++;
	}
	(*i)--;
	new = ft_strnew(count);
	while (--count >= 0)
	{
		new[count] = ch;
	}
	*ar = new;
}

t_list			*ft_get_args(char **read, char ***env, t_cap *cap)
{
	t_list		*node;
	char		*ar;
	int			i;
	char		*str;

	i = 0;
	str = *read;
	node = NULL;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (QUOTE(str[i]))
			ft_is_quote(read, &i, &ar, cap);
		else if (str[i] == '$')
			ft_env_var(str, &i, &ar, *env);
		else if (SPEC(str[i]))
			ft_spec_var(str, &i, &ar);
		else
			ft_args_smpl(str, &i, &ar);
		ft_lstpushback(&node, ar, ft_strlen(ar) + 1);
		ft_strdel(&ar);
		i += (str[i] == '\0' ? 0 : 1);
	}
	return (node);
}
