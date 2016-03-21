/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-monc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/19 02:36:09 by fde-monc          #+#    #+#             */
/*   Updated: 2016/03/22 00:57:32 by fde-monc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *msh_returnval(char *var, t_env **env_list)
{
	t_env *curs;
	
	curs = *env_list;
	while (curs != NULL)
	{
		if (ft_strcmp(var, curs->var) == 0)
			return (curs->val);
		curs = curs->next;
	}
	return (NULL);
}

char	**msh_makeenvtab(t_env **env_list)
{
	int		i;
	char	**tab;
	t_env	*curs;
	char	*tmp;
	
	i = 0;
	curs = *env_list;
	while (curs != NULL)
	{
		i++;
		curs = curs->next;
	}
	tab = malloc(sizeof(char*) * i);
	i = 0;
	curs = *env_list;
	while (curs != NULL)
	{
		tmp = ft_joinjoin(curs->var, "=", curs->val);
		tab[i] = ft_strdup(tmp);
		i++;
		curs = curs->next;
		free(tmp);
	}
	tab[i] = NULL;
	return (tab);
}

t_env	*msh_envcpy(t_env **env_list)
{
	t_env	*new_env;
	t_env	*curs;
	char	*tmp;

	new_env = NULL;
	curs = *env_list;
	while (curs != NULL)
	{
		tmp = ft_joinjoin(curs->var, "=", curs->val);
		msh_makeenv(tmp, &new_env);
		curs=curs->next;
		free(tmp);
	}
	return (new_env);
}

void	msh_switchvar(char *var1, char *var2, t_env **env_list)
{
	t_env	*curs;
	char	*tmp;
	
	tmp = ft_strdup(msh_returnval(var2, env_list));
	curs = *env_list;
	while (curs != NULL)
	{
		if (ft_strcmp(var2, curs->var) == 0)
		{
			free(curs->val);
			curs->val = ft_strdup(msh_returnval(var1, env_list));
		}
		curs=curs->next;
	}
	curs = *env_list;
	while (curs != NULL)
	{
		if (ft_strcmp(var1, curs->var) == 0)
		{
			free(curs->val);
			curs->val = tmp;
		}
		curs = curs->next;
	}
}

int	msh_error(char *index, char *prompt)
{
	if (ft_strcmp(index, "home") == 0)
		ft_putendl("cd: Can't change to home directory.");
	else if (ft_strcmp(index, "chdir") == 0)
		ft_sdebug("%: No such file or directory", prompt);
	else if (ft_strcmp(index, "perm") == 0)
		ft_sdebug("cd: permission denied: %", prompt);
	else
		ft_sdebug("+++++ ANORMAL ERROR AT : % ++++++", prompt);
	return(-1);
}
