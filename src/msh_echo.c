/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-monc <fde-monc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/06 17:10:23 by fde-monc          #+#    #+#             */
/*   Updated: 2016/09/06 17:10:40 by fde-monc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_echo(char **cmd, t_env **env_list)
{
	char	*line;

	if (!env_list)
		return (-1);
	if (!cmd[1])
	{
		ft_putendl("");
		return (1);
	}
	line = echo_makeline(cmd);
	if (echo_checkline(line) != 1)
	{
		ft_putendl("ERROR"); //to change
		return (-1);
	}
	echo_getstring(line);
	ft_putchar('\n');
	return (0);
}

char *echo_makeline(char **cmd) //CHECKED OK
{
	int		i;
	char	*ret;
	char	*ret2;

	ret = ft_strdup(cmd[1]);
	i = 2;
	while (cmd[i])
	{
		ret2 = ft_strdup(ret);
		free(ret);
		ret = ft_joinjoin(ret2, " ", cmd[i]);
		free(ret2);
		i++;
	}
	return (ret);
}


int	echo_getstring(char *line)
{
	char	c;
	int		i;

	i = 0;
	while (line[i])
	{
		while (line[i] && line[i] != '"' && line[i] != 39)
			ft_putchar(line[i++]);
		if ((c = line[i]) == '\0')
			return (1);
		i++;
		while (line[i] && line[i] != c)
			ft_putchar(line[i++]);
		if (line[i] == '\0')
			return (1);
		i++;
	}
	return (1);

}

int	echo_closequote(char *line, int strt)
{
	char	c;
	int		i;
	int		end;

	i = strt;
	c = line[strt];
	if ((end = ft_charindex(line, c)) < 0)
		return (-1);
	while (line[i] && i < end + 1)
	{
		if (line[i] != c)
			ft_putchar(line[i]);
		i++;
	}
	return (1); //??
}

int	echo_checkline(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"')
		{
			i++;
			while (line[i] && line[i] != '"')
				i++;
			if (line[i] == '\0')
				return (-1);
		}
		if (line[i] == 39)
		{
			i++;
			while (line[i] && line[i] != 39)
				i++;
			if (line[i] == '\0')
				return (-1);
		}
		i++;
	}
	return (1);
}
