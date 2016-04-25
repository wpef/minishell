/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_modifenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-monc <fde-monc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 18:31:40 by fde-monc          #+#    #+#             */
/*   Updated: 2016/04/25 20:33:03 by fde-monc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int		msh_unsetenv(char *vari, t_env **env_list)
{
	t_env *curs;

	if (!vari)
		return (msh_error("few", "unsetenv"));
	if ((curs = *env_list) == NULL)
		return (0);
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
			if (curs->next->val)
				free(curs->next->val);
			free(curs->next->var);
			curs->next = curs->next->next;
			return (1);
		}
		curs = curs->next;
	}
	return (0);
}

int		msh_setenv(char *var, char *val, t_env **env_list)
{
	t_env	*curs;
	int		i;

	i = 0;
	if (!var)
		return (msh_printenv(env_list));
	curs = *env_list;
	while (curs != NULL)
	{
		if (ft_strcmp(var, curs->var) == 0)
		{
			if (curs->val)
				free(curs->val);
			curs->val = (val ? ft_strdup(val) : NULL);
			return (1);
		}
		curs = curs->next;
	}
	return (msh_newenv(var, val, env_list));
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
			curs->val ? free(curs->val) : 1;
			curs->val = ft_strdup(msh_returnval(var1, env_list));
		}
		curs = curs->next;
	}
	curs = *env_list;
	while (curs != NULL)
	{
		if (ft_strcmp(var1, curs->var) == 0)
		{
			if (curs->val)
				free(curs->val);
			curs->val = tmp;
		}
		curs = curs->next;
	}
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
		curs = curs->next;
		free(tmp);
	}
	return (new_env);
}
