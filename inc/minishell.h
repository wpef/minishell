/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-monc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 16:05:18 by fde-monc          #+#    #+#             */
/*   Updated: 2016/03/22 00:13:50 by fde-monc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <stdio.h>
# include <sys/param.h>
# define PROMPT ft_putstr("$> ")

typedef struct	s_env {
	char *var;
	char *val;
	struct s_env *next;
}				t_env;

//typedef struct	s_flags { 
//	int i;
//	int u;
//}				t_flags;

void	msh_getcmd(char **cmd, char **env);
void	msh_makeenv(char *envi, t_env **env_list);
char	**msh_splitargs(const char *cmd);
int		msh_checkbuilt(char **cmd, t_env **env_list);

/*
 * msh_env
 */

int		msh_env(char **cmd, t_env *env_list);
int		msh_printenv(t_env **env_list);
int		msh_setenv(char *var, char *val, t_env **env_list);
int		msh_newenv(char *var, char *val, t_env **env_list);
int		msh_unsetenv(char *var, t_env **env_list);

/*
 * msh_chdir
 */

int		msh_chdir(char **cmd, t_env **env_list);
int		msh_gohome(t_env **env_list);
int		msh_switchcwd(t_env **env_list);

/*
 * msh_tools
 */

char	*msh_returnval(char *val, t_env **env_list);
char	**msh_makeenvtab(t_env	**env_list);
void	msh_switchvar(char *var1, char *var2, t_env **env_list);
t_env	*msh_envcpy(t_env **env_list);
int		msh_error(char *index);
void	msh_troll(void);

/*
 * msh_exec
 */

int		msh_exec(char **cmd, t_env	**env_list);
int		msh_execbin(char *binpath, char **flags, char **env);

#endif
