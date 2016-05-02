/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory_error.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 03:47:26 by ishafie           #+#    #+#             */
/*   Updated: 2016/04/03 00:21:22 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			cd_not_found(char *final)
{
	ft_putstr("cd: no such file or directory: ");
	ft_putendl(final);
	return (0);
}

int			cd_error(char *final)
{
	struct stat		sb;
	int				i;
	int				fd;

	fd = -1;
	i = -1;
	if (lstat(final, &sb) == -1)
		ft_putstr("cd: no such file or directory: ");
	else if (!S_ISDIR(sb.st_mode))
		ft_putstr("cd: not a directory: ");
	else if ((sb.st_mode & S_IRUSR) || (fd = open(final, O_RDONLY)) == -1)
		ft_putstr("cd: permission denied: ");
	if (fd != -1)
		close(fd);
	ft_putendl(final);
	return (0);
}
