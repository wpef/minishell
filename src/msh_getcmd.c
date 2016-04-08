/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_getcmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-monc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 16:03:53 by fde-monc          #+#    #+#             */
/*   Updated: 2016/04/08 16:29:33 by fde-monc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_getcmd(char **cmd, t_env **env_list)
{
	int	i;

	i = 0;
	if (msh_checkbuilt(cmd, env_list) == -1)
	{
		if (msh_exec(cmd, env_list) == -1)
			ft_sdebug("minishell: command not found: %", cmd[0]);
	}
}

int		msh_checkbuilt(char **cmd, t_env **env_list)
{
	if (ft_strcmp(cmd[0], "exit") == 0)
	{
		exit(EXIT_SUCCESS);
		return (0);
	}
	if (ft_strcmp(cmd[0], "env") == 0)
	{
		msh_env(cmd, *env_list);
		return (0);
	}
	else if (ft_strcmp(cmd[0], "cd") == 0)
	{
		msh_chdir(cmd, env_list);
		return (0);
	}
	return (msh_checknextbuilt(cmd, env_list));
}

int		msh_checknextbuilt(char **cmd, t_env **env_list)
{
	if (ft_strcmp(cmd[0], "setenv") == 0)
	{
		msh_setenv(cmd[1], cmd[2], env_list);
		return (0);
	}
	else if (ft_strcmp(cmd[0], "unsetenv") == 0)
	{
		msh_parseunset(cmd, env_list);
		return (0);
	}
	return (-1);
}
