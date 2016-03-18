/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-monc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 16:05:18 by fde-monc          #+#    #+#             */
/*   Updated: 2016/03/18 20:53:39 by fde-monc         ###   ########.fr       */
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

t_env	g_env;

void	msh_genvinit(void);
void	msh_getenv(char *envi);
char	**msh_splitargs(const char *cmd);
int		msh_checkbuilt(char **cmd);

/*
 * msh_env
 */

int		msh_env(char **cmd);
int		msh_printenv(void);
int		msh_setenv(char **env, char **cmd);

/*
 * msh_chdir
 */

int		msh_chdir(char **cmd, char **env);

#endif
