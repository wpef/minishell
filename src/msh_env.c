/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-monc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 14:38:10 by fde-monc          #+#    #+#             */
/*   Updated: 2016/03/16 14:46:43 by fde-monc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_getenvi(char **environ, char *name)
{
	int i;
	
	i = 0;
	while (environ[i] != NULL)
	{
		if (ft_strnstr(environ[i], name, ft_strlen(name)) == NULL)
			i++;
		else
		{
			free (environ);
			free (name);
			return (i);
		}
	}
	return (-1);
}
