/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/03 02:36:45 by ishafie           #+#    #+#             */
/*   Updated: 2016/04/03 02:37:29 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			change_env_error(char **args)
{
	ft_putstr("env: illegal option -- ");
	ft_putendl(args[1]);
	ft_putendl("usage: [-i] [-u name]");
	ft_putendl("\t[name=value ...] [utility [argument ...]]");
	return (1);
}
