/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/03 02:45:04 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/02 19:39:23 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			suite_get_all_function(t_env *e, char **args)
{
	if (ft_strcmp(args[0], "unsetenv") == 0)
	{
		if (my_unset_env(e, args) == 1)
		{
			e->nb_env--;
			if (e->path)
			{
				free_args(e->path);
				e->path = NULL;
			}
			refill_path(&e);
			return (1);
		}
		return (1);
	}
	if (ft_strcmp(args[0], "reset") == 0)
	{
		// remettre struct env
		tputs(tgetstr("cl", NULL), 1, ft_putint);
		return (1);
	}
	return (0);
}

int			shlvl(char **suffix)
{
	int		lvl;

	lvl = ft_atoi(*suffix);
	free(*suffix);
	*suffix = ft_itoa(lvl + 1);
	return (1);
}
