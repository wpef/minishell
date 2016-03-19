/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-monc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 14:38:10 by fde-monc          #+#    #+#             */
/*   Updated: 2016/03/19 01:49:35 by fde-monc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_env(char **cmd, t_env *env_list)
{
	int i;
	char **var;
	int j;

	i = 1;
	j = 0;
	if (cmd[i] == NULL)
		return(msh_printenv(&env_list));
	while (cmd[i][j] == '-')
	{
		//gestion flag en struct
		//gere le nouvel env au moment de construire le char** a envoyer a execve
		//if (cmd [i][0] == '\0' || cmd[i][j] == 'i'
		//	|| ft_strcmp(cmd[i], "-ignore-environment") == 0)
		//		flags_i = 1;
		//etc.
		i++;
	}
	var = ft_strsplit(cmd[i], '=');
	msh_setenv(var[0], var[1], &env_list);
	return(0);
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
		return(msh_printenv(env_list));
	curs = *env_list;
	while (curs != NULL)
	{
		if (ft_strcmp(var, curs->var) == 0)
		{
			free(curs->val);
			curs->val = val;
			return (1);
		}
		curs = curs->next;
	}
	return(msh_newenv(var, val, env_list));
}

int	msh_newenv(char *var, char *val, t_env **env_list)
{
	t_env	*curs;
	t_env	*ptr;
	
	curs = *env_list;
	while (curs->next != NULL)
		curs = curs->next;
	ptr = malloc(sizeof(t_env));
	ptr->var = var;
	ptr->val = val;
	ptr->next = NULL;
	curs->next=ptr;
	return(1);
}

int	msh_unsetenv(char *vari, t_env **env_list)
{
	t_env *curs;
	
	curs = *env_list;
	while (vari && curs->next != NULL) //check si curs->next insted of curs pose pas de pb
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
