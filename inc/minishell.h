/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-monc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 16:05:18 by fde-monc          #+#    #+#             */
/*   Updated: 2016/03/19 02:14:55 by fde-monc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <stdio.h>
# define PROMPT ft_putstr("$> ")

typedef struct	s_env {
	char *var;
	char *val;
	//char *str; //for joinjoin(var, =, val); //devrait etre re-done a chaque changement
	struct s_env *next;
}	t_env;

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

int		msh_chdir(char **cmd, char **env);

#endif
