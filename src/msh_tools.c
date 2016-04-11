/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-monc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/19 02:36:09 by fde-monc          #+#    #+#             */
/*   Updated: 2016/04/11 20:47:12 by fde-monc         ###   ########.fr       */
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
	tab = malloc(sizeof(char *) * (i + 1));
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
		msh_cderror(prompt);
	else if (ft_strcmp(index, "argument needed") == 0)
	{
		ft_putendl("env: option requires an argument -- u ");
		msh_usage(0);
	}
	else if (ft_strcmp(index, "invalid argument") == 0)
		ft_sdebug("minishell: % not found", &(prompt[1]));
	else if (ft_strcmp(index, "few") == 0)
		ft_sdebug("%: Too few arguments.", prompt);
	else if (ft_strcmp(index, "many") == 0)
		ft_sdebug("%: Too many arguments.", prompt);
	else
		ft_sdebug("+++++ ANORMAL ERROR AT : % ++++++", prompt);
	return(-1);
}

void	msh_cderror(char *path)
{
	struct stat	s;
	int	i;

	ft_putendl(path);
	i = stat(path, &s);
	if (i == -1)
		ft_sdebug("cd: No such file or directory: %", path);
	else
	{
		if (!S_ISDIR(s.st_mode))
			ft_sdebug("cd: not a directory: %", path);
		else if (access(path, X_OK) == -1)
			ft_sdebug("cd: permission denied: %", path);
	}

}

void	msh_usage(int i)
{
	if (i == 0)
		ft_putendl("usage: env [-i] [-u name]\n[name=value ...] [utility [argument ...]]");
}
