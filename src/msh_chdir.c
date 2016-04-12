/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_chdir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-monc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 14:53:50 by fde-monc          #+#    #+#             */
/*   Updated: 2016/04/12 21:07:58 by fde-monc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_chdir(char **cmd, t_env **env_list)
{
	int		i;
	char	*newpath;

	i = 1;
	newpath = NULL;
	if (msh_returnval("PWD", env_list) == NULL)
		msh_getpwd(env_list);
	if (!cmd[1])
		return (msh_gohome(newpath, NULL, env_list));
	if ((cmd[1][0] == '~') && !cmd[2])
		return (msh_gohome(newpath, cmd[1], env_list));
	if (ft_strcmp(cmd[1], "-") == 0 && !cmd[2])
		return (msh_switchcwd(env_list));
	if (!cmd[2] && chdir(cmd[1]) == 0)
		return (msh_gopath(newpath, env_list));
	else if (cmd[2])
		return (msh_error("many", cmd[0]));
	else
		return (msh_error("chdir", cmd[1]));
}

int	msh_getpwd(t_env **env_list)
{
	char *pwd;

	pwd = NULL;
	if ((pwd = getcwd(pwd, MAXPATHLEN)) != NULL)
	{
		msh_setenv("PWD", pwd, env_list);
		return (1);
	}
	return (-1);
}

int	msh_gopath(char *newpath, t_env **env_list)
{
	if ((newpath = getcwd(newpath, MAXPATHLEN)) != NULL)
	{
		msh_setenv("OLDPWD", newpath, env_list);
		msh_switchvar("PWD", "OLDPWD", env_list);
		free(newpath);
		return (1);
	}
	return (msh_error("getcwd", "msh_chdir line :34"));
}

int	msh_gohome(char *newpath, char *cmd, t_env **env_list)
{
	char *home;
	char *path;

	home = msh_returnval("HOME", env_list);
	if (home)
	{
		if (!cmd)
			path = ft_strdup(home);
		else
			path = ft_strjoin(home, &cmd[1]);
		if (chdir(path) == 0)
			return (msh_gopath(newpath, env_list));
		return (msh_error("chdir", path));
	}
	return (msh_error("home", NULL));
}

int	msh_switchcwd(t_env **env_list)
{
	char	*newpath;
	
	msh_switchvar("PWD", "OLDPWD", env_list);
	if ((newpath = msh_returnval("PWD", env_list)) == NULL)
		return (msh_error("chdir", "cd"));
	if (access(newpath, X_OK) == -1)
		return (msh_error("perm", newpath));
	if (chdir(newpath) != 0)
		return (msh_error("chdir", newpath));
	return (1);
}
