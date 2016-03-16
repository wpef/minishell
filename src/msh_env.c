/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-monc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 14:38:10 by fde-monc          #+#    #+#             */
/*   Updated: 2016/03/16 20:40:02 by fde-monc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_getenvi(char **environ, char *var)
{
	int i;
	
	i = 0;
	while (var && environ[i] != NULL)
	{
		if (ft_strnstr(environ[i], var, ft_strlen(var)) == NULL)
			i++;
		else
			return (i);
	}
	if (environ[i] == NULL)
		return(i);
	return (-1);
}

char	*msh_getenv(char **env, char *var)
{
	int i;
	int len;

	i = msh_getenvi(env, var);
	len = 0;
	if (i >= 0)
	{
		len = ft_strlen(var) + 1; 
		return (ft_strsub(env[i], len, ft_strlen(env[i]) - len));
	}
	else
		return (NULL);
}

int	msh_setenv(char **env, char **cmd)
{
	char *var;
	char *value;
	int i;
	
	i = 0;
	var = ft_strdup(cmd[1]);
	value = (cmd[1] ? ft_strdup(cmd[2]) : NULL); //if cmd[1] NULL, [2] segv
	if (!var)
		ft_print_tab(env);
	else
	{
		i = msh_getenvi(env, var);
		if (env[i] != NULL) //var existe dans env
			ft_bzero(env[i], ft_strlen(env[i]));
		env[i] = ft_joinjoin(var,"=",value);
		return (1);
	}
	return (0); // check what to do en fonction de return
}
