/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-monc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 14:38:10 by fde-monc          #+#    #+#             */
/*   Updated: 2016/04/06 22:15:34 by fde-monc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_env(char **cmd, t_env *env_list)
{
	int i;
	char **var;
	int j;
	t_env	*newenv_list;

	i = 1;
	j = 0;
	newenv_list = msh_envcpy(&env_list);
	while (cmd[i] && cmd[i][0] == '-')
	{
		if (cmd[i][1] == 'i')
			newenv_list = NULL;
		else if (cmd[i][1] == 'u')
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
		i++;
	}
	if (cmd[i] && cmd[i][0] != '\0')
	{
	//	free cmd -> cmd[i];
		cmd = &cmd[i];
		msh_getcmd(cmd, &newenv_list);
	}
	else
		return (msh_printenv(&newenv_list));
	return (0);
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

int	msh_setenv(char *var, char *val, t_env **env_list)
{
	t_env	*curs;
	int i;
	
	i = 0;
	if (!var)
		return (msh_printenv(env_list));
	curs = *env_list;
	while (curs != NULL)
	{
		if (ft_strcmp(var, curs->var) == 0)
		{
			free(curs->val);
			curs->val = (val ? val : NULL);
			return (1);
		}
		curs = curs->next;
	}
	return (msh_newenv(var, val, env_list));
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
	ptr->var = var;
	ptr->val = val;
	ptr->next = NULL;
	if (*env_list == NULL)
	{
		*env_list = ptr;
		return (1);
	}
	curs->next=ptr;
	return (1);
}
int		msh_parseunset(char **cmd, t_env **env_list)
{
	int	i;

	i = 1;
	if (cmd[i] == NULL)
		return (msh_error("few", "unsetenv"));
	while (cmd[i] != NULL && cmd[i][0] != '\0')
	{
		msh_unsetenv(cmd[i], env_list);
		i++;
	}
	return (0);
}

int	msh_unsetenv(char *vari, t_env **env_list)
{
	t_env *curs;
	
	if (!vari)
		return (msh_error("few", "unsetenv"));
	curs = *env_list;
	if (vari && ft_strcmp(vari, curs->var) == 0)
	{
		*env_list = curs->next;
		free(curs);
		return (1);
	}
	while (vari && curs->next != NULL)
	{
		if (ft_strcmp(vari, curs->next->var) == 0)
		{
			free(curs->next);
			curs->next = curs->next->next;
			return (1);
		}
		curs = curs->next;
	}
	return (0);
}
