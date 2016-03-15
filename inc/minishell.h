/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-monc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 16:05:18 by fde-monc          #+#    #+#             */
/*   Updated: 2016/03/15 19:06:11 by fde-monc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# define PROMPT ft_putstr("$> ")

int		msh_checkcmd(char **cmd);
char	**msh_splitargs(const char *cmd);
int		msh_execbin(char **cmd);
int		msh_checkbuilt(char **cmd);

#endif
