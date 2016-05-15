/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 15:32:15 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/14 17:42:33 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			redirection_error(char **line, int a)
{
	struct stat		sb;
	int				i;

	i = -1;
	ft_putstr_fd("42sh: ", 2);
	ft_putstr_fd(line[a], 2);
	if (lstat(line[a], &sb) == -1)
		ft_putstr_fd(": No such file or directory\n", 2);
	else if (S_ISDIR(sb.st_mode))
		ft_putstr_fd(": Is a directory\n", 2);
	else if ((sb.st_mode & S_IWUSR) != 1)
		ft_putstr_fd(": Permission denied\n", 2);
	return (-1);
}
