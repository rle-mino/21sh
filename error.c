/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 16:40:55 by ishafie           #+#    #+#             */
/*   Updated: 2016/04/27 04:20:59 by ishafie          ###   ########.fr       */
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
	ft_putstr("zsh : command not found: ");
	ft_putstr(line);
	ft_putstr(" and more than that ");
	ft_putstr(str);
	ft_putstr(" can't be found either.\n");
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
		ft_putstr("zsh: no such file or directory: ");
		ft_putendl(&line[1]);
		return (NULL);
	}
	ft_putstr("zsh: command not found: ");
	i = get_name(line);
	ft_putstr(&line[i]);
	ft_putchar('\n');
	return (NULL);
}

char	*error_handler(char *tmp)
{
	if (access(tmp, X_OK) == 0)
		return (tmp);
	else
		return (error_exe(tmp));
}
