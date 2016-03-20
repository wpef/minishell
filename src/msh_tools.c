/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-monc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/19 02:36:09 by fde-monc          #+#    #+#             */
/*   Updated: 2016/03/20 22:20:14 by fde-monc         ###   ########.fr       */
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
			return(curs->val);
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
	return(tab);
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
	return(new_env);
}

t_env	*msh_varcpy(t_env *src)
{
	t_env *new;
	new = malloc(sizeof(t_env));
	new->var = ft_strdup(src->var);
	new->val = ft_strdup(src->val);
	new->next = NULL;
	return(new);
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
