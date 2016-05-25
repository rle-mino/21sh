/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 00:40:59 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/26 00:41:54 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			change_env_error(char **args)
{
	ft_putstr_fd("env: illegal option -- ", 2);
	ft_putendl_fd(args[1], 2);
	ft_putendl_fd("usage: [-i] [-u name]", 2);
	ft_putendl_fd("\t[name=value ...] [utility [argument ...]]", 2);
	return (1);
}
