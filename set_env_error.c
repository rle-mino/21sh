/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/02 23:32:54 by ishafie           #+#    #+#             */
/*   Updated: 2016/04/02 23:42:20 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				unset_check(char **args)
{
	if (args[1] && args[2])
		return (set_env_error(0));
	if (!args[1])
		return (set_env_error(3));
	return (1);
}

int				set_env_error(int a)
{
	if (a == 1)
		ft_putstr("setenv: too many arguments\n");
	else if (a == 0)
		ft_putstr("unsetenv: too many arguments\n");
	else if (a == 2)
		ft_putstr("setenv: too few arguments\n");
	else if (a == 3)
		ft_putstr("unsetenv: too few arguments\n");
	return (0);
}
