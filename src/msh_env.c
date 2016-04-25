/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-monc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 14:38:10 by fde-monc          #+#    #+#             */
/*   Updated: 2016/04/25 18:49:57 by fde-monc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_env(char **cmd, t_env *env_list)
{
	int		i;
	int		j;
	t_env	*newenv_list;

	j = 0;
	newenv_list = msh_envcpy(&env_list);
	i = msh_envflags(cmd, newenv_list);
	if (cmd[i] && cmd[i][0] != '\0')
	{
		while (j < i)
		{
			free(cmd[j]);
			j++;
		}
		cmd = &cmd[i];
		msh_getcmd(cmd, &newenv_list);
	}
	else
		return (msh_printenv(&newenv_list));
	return (0);
}

int		msh_envflags(char **cmd, t_env *newenv_list)
{
	int		i;
	char	**var;

	i = 1;
	while (cmd[i] && cmd[i][0] == '-')
	{
		if (ft_strcmp(cmd[i], "-i") == 0)
			newenv_list = NULL;
		else if (ft_strcmp(cmd[i], "-u") == 0)
		{
			i++;
			if (cmd[i])
				msh_unsetenv(cmd[i], &newenv_list);
			else
				return (msh_error("argument needed", cmd[i - 1]));
		}
		i++;
	}
	while (ft_charindex(cmd[i], '=') >= 0)
	{
		if (ft_charindex(cmd[i], '=') == 0)
			return (msh_error("invalid argument", cmd[i]));
		var = ft_strsplit(cmd[i], '=');
		msh_setenv(var[0], var[1], &newenv_list);
		free(var);
		i++;
	}
	return (i);
}

int	msh_printenv(t_env **env_list)
{
	t_env	*curs;

	curs = *env_list;
	while (curs != NULL)
	{
		ft_putstr(curs->var);
		ft_putchar('=');
		ft_putendl(curs->val ? curs->val : "");
		curs = curs->next;
	}
	return (1);
}

int	msh_newenv(char *var, char *val, t_env **env_list)
{
	t_env	*curs;
	t_env	*ptr;

	curs = *env_list;
	if (curs)
	{
		while (curs->next != NULL)
			curs = curs->next;
	}
	ptr = malloc(sizeof(t_env));
	ptr->var = ft_strdup(var);
	ptr->val = ft_strdup(val);
	ptr->next = NULL;
	if (*env_list == NULL)
	{
		*env_list = ptr;
		return (1);
	}
	curs->next = ptr;
	return (1);
}
