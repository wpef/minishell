/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_chdir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-monc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 14:53:50 by fde-monc          #+#    #+#             */
/*   Updated: 2016/03/19 05:32:14 by fde-monc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_chdir(char **cmd, t_env **env_list)
{
	int i;

	if (!cmd[1] || ft_strcmp(cmd[1], "~") == 0)
	{
		msh_gohome(env_list);
		return(1);
	}
	i = 1;
	while (cmd[i][0] == '-')
	{
		if (cmd[i][1] == '\0')
		{
			msh_switchvar("PWD", "OLDPWD", env_list);
			chdir(msh_returnval("PWD", env_list));
			return(1);
		}
		//gestion flags
		i++;
	}
	msh_setenv("OLDPWD", cmd[i], env_list); //ecrit nouveau chemin dans oldpwd
	msh_switchvar("PWD", "OLDPWD", env_list); //echange old et new
	chdir(msh_returnval("PWD", env_list));
	return(0);
}

int	msh_gohome(t_env **env_list)
{
	char *home;

	home = ft_strdup(msh_returnval("HOME", env_list));
	chdir(home);
	msh_setenv("OLDPWD", ft_strdup(msh_returnval("PWD", env_list)), env_list);
	msh_setenv("PWD", home, env_list);
	return(1);
}
