/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-monc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 14:38:10 by fde-monc          #+#    #+#             */
/*   Updated: 2016/03/18 23:11:20 by fde-monc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_env(char **cmd, t_env *env_list)
{
	int i;

	i = 1;
	if (cmd[i] == NULL)
		return(msh_printenv(&env_list));
	while (cmd[i][0] == '-')
	{
		//gestion flags
		i++;
	}
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

int	msh_setenv(char **cmd, t_env **env_list) //TOUT FAUX EVIDEMMENT
{
	char *var;
	char *val;
	t_env	*curs;
	int i;
	
	i = 0;
	var = ft_strdup(cmd[1]);
	val = (cmd[1] ? ft_strdup(cmd[2]) : NULL); //if cmd[1] NULL, [2] segv
	if (!var)
		return(msh_env(cmd, *env_list));
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
