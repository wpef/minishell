/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-monc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/19 02:18:28 by fde-monc          #+#    #+#             */
/*   Updated: 2016/03/19 03:21:22 by fde-monc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int msh_exec(char **cmd, t_env **env_list) //if bin direct
{
	char	**paths;
	char	*binpath;
	char	**env_tab;
	int		i;

	i = 0;
	paths = ft_strsplit(msh_returnval("PATH", env_list), ':');
	env_tab = msh_makeenvtab(env_list);
	while (paths[i])
	{
		binpath = ft_joinjoin(paths[i], "/", cmd[0]);
		if (msh_execbin(binpath, cmd, env_tab) == 1)
			return(1);
		i++;
		free(binpath);
	}
	return (-1);
}

int	msh_execbin(char *binpath, char **flags, char **env)
{
	pid_t	pid;
	
	pid = fork();
	if (pid == 0)
		return(execve(binpath, flags, env));
	else
		wait (&pid);
	return(1);
}
