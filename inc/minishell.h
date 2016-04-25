/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-monc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 16:05:18 by fde-monc          #+#    #+#             */
/*   Updated: 2016/04/25 18:07:48 by fde-monc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <sys/param.h>
# include <sys/stat.h>
# define PROMPT ft_putstr("$> ")

typedef struct	s_env {
	char			*var;
	char			*val;
	struct s_env	*next;
}				t_env;

/*
** msh_main
*/

void			msh_readline(t_env **env_list);
void			msh_makeenv(char *envi, t_env **env_list);

/*
**	msh_getcmd
*/

void			msh_getcmd(char **cmd, t_env **env);
char			**msh_splitargs(const char *cmd);
int				msh_checkbuilt(char **cmd, t_env **env_list);
int				msh_checknextbuilt(char **cmd, t_env **env_list);

/*
** msh_env
*/

int				msh_env(char **cmd, t_env *env_list);
int				msh_printenv(t_env **env_list);
int				msh_setenv(char *var, char *val, t_env **env_list);
int				msh_newenv(char *var, char *val, t_env **env_list);
int				msh_unsetenv(char *var, t_env **env_list);
int				msh_parseunset(char **cmd, t_env **env_list);

/*
** msh_chdir
*/

int				msh_chdir(char **cmd, t_env **env_list);
int				msh_getpwd(t_env **env_list);
int				msh_gopath(char *newpath, t_env **env_list);
int				msh_gohome(char *newpath, char *cmd, t_env **env_list);
int				msh_switchcwd(t_env **env_list);

/*
** msh_tools
*/

char			*msh_returnval(char *val, t_env **env_list);
char			**msh_makeenvtab(t_env	**env_list);
void			msh_switchvar(char *var1, char *var2, t_env **env_list);
t_env			*msh_envcpy(t_env **env_list);
int				msh_error(char *index, char *prompt);
void			msh_cderror(char *path);
void			msh_usage(int i);

/*
** msh_exec
*/

int				msh_exec(char **cmd, t_env **env_list);
int				msh_execbin(char *binpath, char **flags, char **env);
int				msh_execpath(char **cmd, char **env_tab);
char			**msh_getpaths(t_env **env_list);

#endif
