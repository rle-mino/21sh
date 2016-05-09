/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_fnt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 13:38:26 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/07 21:41:34 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		seg_exit(void)
{
	ft_putstr_fd("minishell: segmentation fault  ", 2);
	ft_putendl_fd(g_name_prog, 2);
}

void			safe_exit(int a)
{
	char	c;

	c = 0;
	if (a == SIGINT)
	{
		return ;
	}
	if (a == SIGSEGV)
		seg_exit();
}
