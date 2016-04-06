/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_chdir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-monc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 14:53:50 by fde-monc          #+#    #+#             */
/*   Updated: 2016/04/06 21:48:52 by fde-monc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_chdir(char **cmd, t_env **env_list)
{
	int i;
	char *newpath;

	i = 1;
	newpath = NULL;
	if (!cmd[1] || cmd[1][0] == '~')
		return(msh_gohome(env_list));
	if (ft_strcmp(cmd[1], "-") == 0)
		return(msh_switchcwd(env_list));
	if (/*!cmd[2] &&*/chdir(cmd[1]) == 0) //comment pour gestion switch;
	{
		if ((newpath = getcwd(newpath, MAXPATHLEN)) != NULL)
		{
			msh_setenv("OLDPWD", newpath, env_list);
			msh_switchvar("PWD", "OLDPWD", env_list);
			return (1);
		}
		return (msh_error("getcwd", "msh_chdir line :34"));
	}
	else if (cmd[2])
		return (msh_error("many", cmd[1]));
	else
		return (msh_error("chdir", cmd[1]));
}

int	msh_gohome(t_env **env_list)
{
	char *home;

	home = ft_strdup(msh_returnval("HOME", env_list));
	if (home)
	{
		if (access(home, X_OK) == -1)
			return (msh_error("perm", home));
		if (chdir(home) == 0)
		{
			msh_setenv("OLDPWD", ft_strdup(msh_returnval("PWD", env_list)), env_list);
			msh_setenv("PWD", home, env_list);
			return (1);
		}
	}
	return(msh_error("home", NULL));
}

int	msh_switchcwd(t_env **env_list)
{
	char	*newpath;
	
	msh_switchvar("PWD", "OLDPWD", env_list);
	if ((newpath = msh_returnval("PWD", env_list)) == NULL)
		return (msh_error("chdir", "cd"));
	if (access(newpath, X_OK) == -1)
		return(msh_error("perm", newpath));
	if (chdir(newpath) != 0)
		return(msh_error("chdir", newpath));
	return (1);
}
