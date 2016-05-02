/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_rwx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/27 17:47:49 by ishafie           #+#    #+#             */
/*   Updated: 2016/04/03 04:25:56 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			error_no_exec(char *tmp)
{
	int		i;

	i = get_name(tmp);
	ft_putstr("zsh: exec format error: ");
	ft_putstr(&tmp[i]);
	ft_putchar('\n');
	return (-1);
}

char		*error_exe(char *tmp)
{
	struct stat			sb;
	int					i;

	i = get_name(tmp);
	if (lstat(tmp, &sb) == -1)
		return (NULL);
	if (!(S_IXUSR & sb.st_mode))
	{
		ft_putstr("zsh: permission denied: ");
		ft_putstr(&tmp[i]);
		ft_putchar('\n');
	}
	return (NULL);
}
