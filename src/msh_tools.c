/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-monc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/19 02:36:09 by fde-monc          #+#    #+#             */
/*   Updated: 2016/09/06 17:45:21 by fde-monc         ###   ########.fr       */
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
		ft_putendl_fd("cd: Can't change to home directory.", 2);
	else if (ft_strcmp(index, "chdir") == 0)
		msh_cderror(prompt);
	else if (ft_strcmp(index, "argument needed") == 0)
	{
		ft_putendl_fd("env: option requires an argument -- u ", 2);
		ft_putendl_fd("usage: env [-i] [-u name]", 2);
		ft_putendl_fd("[name=value ...] [utility [argument ...]]", 2);
	}
	else if (ft_strcmp(index, "invalid argument") == 0)
		msh_erroralert("minishell: % not found", &(prompt[1]));
	else if (ft_strcmp(index, "few") == 0)
		msh_erroralert("%: Too few arguments.", prompt);
	else if (ft_strcmp(index, "many") == 0)
		msh_erroralert("%: Too many arguments.", prompt);
	else if (ft_strcmp(index, "quote") == 0)
		msh_erroralert("%: Unmatched quote or simple quote", prompt);
	else
		msh_erroralert("+++++ ANORMAL ERROR AT : % ++++++", prompt);
	return (-1);
}

void	msh_cderror(char *path)
{
	struct stat	s;
	int			i;

	i = stat(path, &s);
	if (i == -1)
		msh_erroralert("cd: No such file or directory: %", path);
	else
	{
		if (!S_ISDIR(s.st_mode))
			msh_erroralert("cd: not a directory: %", path);
		else if (access(path, X_OK) == -1)
			msh_erroralert("cd: permission denied: %", path);
	}
}

void	msh_erroralert(char *str, char *s)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '%')
			ft_putchar_fd(str[i], 2);
		if (str[i] == '%')
		{
			if (s == NULL)
				return (ft_putstr_fd("NULL", 2));
			while (s[j])
			{
				ft_putchar_fd(s[j], 2);
				j++;
			}
		}
		i++;
	}
	ft_putchar_fd('\n', 2);
}
