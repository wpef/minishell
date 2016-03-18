/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-monc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 14:38:10 by fde-monc          #+#    #+#             */
/*   Updated: 2016/03/18 20:55:36 by fde-monc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_env(char **cmd)
{
	if (cmd[1] == NULL)
		return(msh_printenv());
	return(0);
}

int	msh_printenv(void)
{
	t_env	*curs;

	curs = &g_env;
	while (curs != NULL)
	{
		ft_putstr(curs->var);
		ft_putchar('=');
		ft_putendl(curs->val);
		curs = curs->next;
	}
	return (1);
}

int	msh_setenv(char **env, char **cmd) //TOUT FAUX EVIDEMMENT
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
		if (env[i] != NULL) //var existe dans env
			ft_bzero(env[i], ft_strlen(env[i]));
		env[i] = ft_joinjoin(var,"=",value);
		return (1);
	}
	return (0); // check what to do en fonction de return
}
