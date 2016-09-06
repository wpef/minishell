/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-monc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/19 02:36:09 by fde-monc          #+#    #+#             */
/*   Updated: 2016/09/06 17:18:19 by fde-monc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*msh_returnval(char *var, t_env **env_list)
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

int		msh_error(char *index, char *prompt)
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
	else if (ft_strcmp(index, "quote") == 0)
		ft_sdebug("%: Unmatched quote or simple quote", prompt);
	else
		ft_sdebug("+++++ ANORMAL ERROR AT : % ++++++", prompt);
	return (-1);
}

void	msh_cderror(char *path)
{
	struct stat	s;
	int			i;

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
	{
		ft_putendl("usage: env [-i] [-u name]");
		ft_putendl("[name=value ...] [utility [argument ...]]");
	}
}
