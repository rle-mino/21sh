/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 00:28:35 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/26 00:29:00 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			how_to_tab(t_env *e, char **args)
{
	t_arbre *a;
	char	*mot;

	mot = (char*)malloc(sizeof(char) * 100);
	ft_bzero(mot, 100);
	creer_arbre(&(e->tb), args[1]);
	a = e->tb;
	e->tb = recherche(&(e->tb), args[2]);
	completion_tree(e->tb, &mot, 0);
	free_arbre(&a);
	e->tb = NULL;
	return (1);
}

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
		tputs(tgetstr("cl", NULL), 1, ft_putint);
		return (1);
	}
	if (ft_strcmp(args[0], "tab") == 0)
		return (how_to_tab(e, args));
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
