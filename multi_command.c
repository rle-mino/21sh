/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 16:50:10 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/02 18:34:42 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			get_nb_cmd(char *line)
{
	int		nb_cmd;
	int		i;

	i = 0;
	nb_cmd = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] == ';')
			nb_cmd++;
		i++;
	}
	if (nb_cmd == 0)
		return (1);
	return (nb_cmd + 1);
}

static void	last_command(char **line, char **new_line)
{
	ft_strdel(line);
	*line = ft_strdup(*new_line);
	ft_strdel(new_line);
}

void		actualise_command(char **line, char **new_line, int cmd, int n_cmd)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	if (cmd == n_cmd - 1)
		return (last_command(line, new_line));
	if (*new_line)
	{
		ft_strdel(line);
		*line = ft_strdup(*new_line);
		ft_strdel(new_line);
	}
	len = ft_strlen(*line);
	while ((*line)[i] && (*line)[i] != ';')
		i++;
	*new_line = ft_strsub(*line, 0, i);
	tmp = ft_strsub(*line, i + 1, len - (i + 1));
	ft_strdel(line);
	*line = ft_strdup(*new_line);
	ft_strdel(new_line);
	*new_line = tmp;
}
