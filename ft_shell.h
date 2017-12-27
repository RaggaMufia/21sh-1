/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skavunen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 14:27:06 by skavunen          #+#    #+#             */
/*   Updated: 2017/08/23 14:01:27 by skavunen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHELL_H
# define FT_SHELL_H
# include <termios.h>
# include <unistd.h>
# include <stdio.h>
# include <curses.h>
# include <term.h>
# include <string.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>

# define ARGWL(x) x != '\0' && x != ' ' && x != '\t' && x != ';' && x != '|'
# define KEY(x) x == 8 || x == 127 || x == 27 || x == 9 || x == 18
# define KEY2(x) x == 11 || x == 12
# define QUOTE(x) x == '\'' || x == '"' || x == '`'
# define SPEC(x) x == ';' || x == '|' || x == '>' || x == '<'
# define MYCMD(x) !ft_strcmp(x, "cd") || !ft_strcmp(x, "setenv")
# define MYCMD2(x) !ft_strcmp(x, "env") || !ft_strcmp(x, "unsetenv")

t_list					*g_hist;

pid_t					g_proc;

typedef struct termios	t_term;
typedef struct dirent	t_dirent;

typedef struct	s_cap
{
	char	*tgo;
	char	*left;
	char	*deline;
	int		x;
	int		y;
	int		mx;
	int		my;
}				t_cap;

typedef struct	s_inp
{
	int		ind;
	char	*arg;
	int		hist;
	char	*hst;
	t_list	*cpl;
	int		cplind;
	int		cplen;
	int		cplprev;
}				t_inp;

t_inp					*g_inp;
t_term					g_old;
t_term					g_new;

typedef struct	s_fds
{
	int		fd[2];
	int		in;
	int		close;
	int		open;
	int		file;
	int		hdoc;
	char	*hered;
	int		mem1;
	int		mem2;
	int		mem3;
	int		ex[2];
}				t_fds;

void			ft_sig_cont(int sig);
void			ft_reset_tab(t_inp *inp);
void			ft_home_end(char ch, t_inp *inp);
void			ft_21sh(t_cap *cap, char ***env);
t_term			ft_init_term(void);
char			**ft_init_env(char **env);
t_cap			*ft_init_cap(void);
int				ft_put(int ch);
char			*ft_input(t_cap *cap);
t_inp			*ft_init_inp(void);
void			ft_is_quote(char **str, int *a, char **ar, t_cap *cap);
int				ft_find_env(char **env, char *find, int cmp);
t_list			*ft_get_args(char **read, char ***env, t_cap *cap);
void			ft_backspace(t_cap *cap, t_inp *inp, char **arg);
void			ft_arrows(t_cap *cap, t_inp *inp, char **arg);
void			ft_tab(t_cap *cap, t_inp *inp, char **arg);
void			ft_up_arrow(t_cap *cap, t_inp *inp, char **arg);
void			ft_down_arrow(t_cap *cap, t_inp *inp, char **arg);
void			ft_lst_cmd(t_list *list, char **env, t_cap *cap);
t_list			*ft_node_split(t_list *node, char *split);
int				ft_lst_len(t_list *list);
char			**ft_lstochar(t_list *list);
void			ft_exe_list(t_list *node, char **env, t_cap *cap);
void			ft_go_home(t_inp *inp);
char			*ft_findexe(char *cmd, char **env);
char			*ft_findpath(char *env, char *cmd);
int				ft_fileexist(char *name);
int				ft_tofile(char **arg, int *file);
void			ft_del_split(t_list **list);
void			ft_del_list(t_list **list);
void			ft_del_arg(char ***str);
void			ft_del_tmp(t_list **tmp);
t_fds			*ft_init_fds(void);
void			ft_check_for_file(t_fds *fds, t_list **list);
void			ft_set_fds(t_fds *fds, char ***str);
int				ft_check_redirect(char *str);
int				ft_check_amper(char *str);
void			ft_hist_search(t_cap *cap, t_inp *inp, char **arg);
void			ft_execute(t_list *node, char ***env, t_fds *fds);
void			ft_command(char *cmd, t_list *node, char ***env);
void			ft_un_fds(t_fds **del);
void			ft_exe_pipes(t_list *node, char ***env);
void			ft_exec_pipe(t_fds *fds, char **arg, char **env);
void			ft_error_cmd(char *cmd);
void			ft_m_setenv(t_list *list, char ***env);
void			ft_m_unsetenv(t_list *list, char **env);
void			ft_mini_cd(t_list *list, char ***env);
void			ft_heredoc(t_fds *fds, char **arg, char **env, int fl);
void			ft_dup_fds(t_fds *fds, int fl);
void			ft_fdsfile(t_fds *fds, int *flag);
void			ft_ctrl_up(t_inp *inp, int *flag);
void			ft_ctrl_do(t_inp *inp, int *flag);
void			ft_ctrl_ri(t_inp *inp);
void			ft_ctrl_le(t_inp *inp);
int				ft_check_arg(char **arg);

#endif
