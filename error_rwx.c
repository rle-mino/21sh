/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_rwx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/27 17:47:49 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/07 21:30:43 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			error_no_exec(char *tmp)
{
	int		i;

	i = get_name(tmp);
	ft_putstr_fd("zsh: exec format error: ", 2);
	ft_putstr_fd(&tmp[i], 2);
	ft_putchar_fd('\n', 2);
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
		ft_putstr_fd("zsh: permission denied: ", 2);
		ft_putstr_fd(&tmp[i], 2);
		ft_putchar_fd('\n', 2);
	}
	return (NULL);
}
