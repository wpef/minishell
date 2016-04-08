/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-monc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/19 02:18:28 by fde-monc          #+#    #+#             */
/*   Updated: 2016/04/08 17:14:18 by fde-monc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		msh_exec(char **cmd, t_env **env_list) //if bin direct
{
	char	**paths;
	char	*path;
	char	**env_tab;
	int		i;

	i = 0;
	paths = msh_getpaths(cmd, env_list);
	//debug
	ft_putendl("DEBUG === ");
	if (paths)
	{
		while (paths[i])
		{
			ft_putendl(paths[i]);
			i++;
		}
	}
	i = 0;
	//eof debug
	env_tab = msh_makeenvtab(env_list);
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

char	**msh_getpaths(char **cmd, t_env **env_list)
{
	char	*path;
	char	**paths;

	paths = NULL;
	if (cmd[0][0] == '/')
	{
		paths = malloc(sizeof (char*) * 2);
		paths[0] = cmd[0];
		paths[1] = NULL;
	}
	else
	{
		path = msh_returnval("PATH", env_list);
		if (path == NULL)
			paths = ft_strsplit("/usr/bin:/bin", ':');
		else
			paths = ft_strsplit(path, ':');
	}
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
		wait (&pid);
	return (1);
}
