/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_chdir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-monc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 14:53:50 by fde-monc          #+#    #+#             */
/*   Updated: 2016/03/22 00:12:17 by fde-monc         ###   ########.fr       */
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
			msh_setenv("PWD", ft_strdup(newpath), env_list);
			free(newpath);
			return (1);
		}
		return (msh_error("getcwd"));
	}
	//gestion switch ?
	else
		return(msh_error("chdir"));
	return (0);
}

int	msh_gohome(t_env **env_list)
{
	char *home;

	home = ft_strdup(msh_returnval("HOME", env_list));
	if (home)
	{
		if (chdir(home) == 0)
		{
			msh_setenv("OLDPWD", ft_strdup(msh_returnval("PWD", env_list)), env_list);
			msh_setenv("PWD", home, env_list);
			return (1);
		}
	}
	return(msh_error("home"));
}

int	msh_switchcwd(t_env **env_list)
{
	char	*newpath;
	
	msh_switchvar("PWD", "OLDPWD", env_list);
	newpath = msh_returnval("PWD", env_list);
	if (access(newpath, X_OK) == -1)
		return(msh_error("perm"));
	if (chdir(newpath) != 0)
		return(msh_error("chdir"));
	return (1);
}
