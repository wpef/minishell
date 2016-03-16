/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-monc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 16:05:18 by fde-monc          #+#    #+#             */
/*   Updated: 2016/03/16 21:04:02 by fde-monc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <stdio.h>
# define PROMPT ft_putstr("$> ")

char	**msh_splitargs(const char *cmd);
int		msh_execbin(char **cmd);
int		msh_checkbuilt(char **cmd, char **environ);
void	ft_print_tab(char **tab); //go libft

/*
 * msh_env
 */

int		msh_getenvi(char **env, char *name);
int		msh_setenv(char **env, char **cmd);
char	*msh_getenv(char **env, char *var);

/*
 * msh_chdir
 */

int		msh_chdir(char **cmd, char **env);

#endif
