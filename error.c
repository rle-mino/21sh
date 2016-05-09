/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 16:40:55 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/07 21:29:37 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_handling(void)
{
	ft_putstr_fd("Allocation failure, exiting..\n", 2);
	exit(EXIT_FAILURE);
}

int		error_path_not_found(char *str, char *line)
{
	ft_putstr_fd("zsh : command not found: ", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd(" and more than that ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" can't be found either.\n", 2);
	return (-1);
}

int		get_name(char *line)
{
	int		save;
	int		i;

	i = 0;
	save = i;
	while (line[i] != '\0')
	{
		if (line[i] == '/')
			save = i + 1;
		i++;
	}
	return (save);
}

char	*error_not_found(char *line)
{
	int		i;

	i = 0;
	if (get_name(&line[1]) != 0)
	{
		ft_putstr_fd("zsh: no such file or directory: ", 2);
		ft_putendl_fd(&line[1], 2);
		return (NULL);
	}
	ft_putstr_fd("zsh: command not found: ", 2);
	i = get_name(line);
	ft_putstr_fd(&line[i], 2);
	ft_putchar_fd('\n', 2);
	return (NULL);
}

char	*error_handler(char *tmp)
{
	if (access(tmp, X_OK) == 0)
		return (tmp);
	else
		return (error_exe(tmp));
}
