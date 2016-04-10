/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-monc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/19 02:18:28 by fde-monc          #+#    #+#             */
/*   Updated: 2016/04/10 22:13:45 by fde-monc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		msh_exec(char **cmd, t_env **env_list)
{
	char	**paths;
	char	*path;
	char	**env_tab;
	int		i;

	i = 0;
	env_tab = msh_makeenvtab(env_list);
	if (cmd[0][0] == '/')
		return (msh_execpath(cmd, env_tab));
	paths = msh_getpaths(env_list);
	while (paths[i])
	{
		path = ft_joinjoin(paths[i], "/", cmd[0]);
		if (access(path, F_OK) == 0)
		{
			msh_execbin(path, cmd, env_tab);
			return (1);
		}
		i++;
		free(path);
	}
	return (-1);
}

int		msh_execpath(char **cmd, char **env_tab)
{
	char	*path;

	path = cmd[0];
	if (access(path, F_OK) == 0)
	{
		msh_execbin(path, cmd, env_tab);
		return (1);
	}
	return (-1);
}

char	**msh_getpaths(t_env **env_list)
{
	char	*path;
	char	**paths;

	path = msh_returnval("PATH", env_list);
	if (path == NULL)
		paths = ft_strsplit("/usr/bin:/bin", ':');
	else
		paths = ft_strsplit(path, ':');
	return (paths);
}

int		msh_execbin(char *binpath, char **flags, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (execve(binpath, flags, env) == -1)
			return (-1);
	}
	else
		wait(&pid);
	return (1);
}
