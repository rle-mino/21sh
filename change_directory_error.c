/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory_error.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 00:40:39 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/26 00:40:55 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			cd_not_found(char *final)
{
	ft_putstr_fd("cd: no such file or directory: ", 2);
	ft_putendl_fd(final, 2);
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
		ft_putstr_fd("cd: no such file or directory: ", 2);
	else if (!S_ISDIR(sb.st_mode))
		ft_putstr_fd("cd: not a directory: ", 2);
	else if ((sb.st_mode & S_IRUSR) || (fd = open(final, O_RDONLY)) == -1)
		ft_putstr_fd("cd: permission denied: ", 2);
	if (fd != -1)
		close(fd);
	ft_putendl_fd(final, 2);
	return (0);
}
