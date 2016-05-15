/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 22:55:43 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/16 00:13:29 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"
#include "minishell.h"

int				is_folder(char *name)
{
	struct stat		statb;

	if (!stat(name, &statb) && S_ISDIR(statb.st_mode))
		return (1);
	return (0);
}

char			**get_path_and_word(char *str)
{
	int			i;
	char		**path_and_word;

	i = ft_strlen(str) - 1;
	path_and_word = ft_memalloc(sizeof(char *) * 2);
	while (i > 0)
	{
		if (str[i] == '/')
		{
			path_and_word[0] = ft_strsub(str, 0, i);
			path_and_word[1] = ft_strdup(str + i + 1);
			return (path_and_word);
		}
		i--;
	}
	path_and_word[0] = ft_strdup(".");
	path_and_word[1] = ft_strdup(str);
	return (path_and_word);
}

static char		**get_actual_word(t_line *line)
{
	char		buffer[1024];
	char		**path_and_word;
	int			i;

	i = 0;
	ft_bzero(buffer, sizeof(buffer));
	while (line && line->prev && line->c != ' ')
		line = line->prev;
	if (line && (line->c == ' ' || line->c == '\0'))
		line = line->next;
	while (line && line->c != ' ')
	{
		buffer[i] = line->c;
		i++;
		line = line->next;
	}
	path_and_word = get_path_and_word(buffer);
	return (path_and_word);
}

void			complete_word(t_line **line, t_le *le)
{
	char		**path_and_word;
	char		*buffer;
	t_arbre		arbre;
	t_arbre		tmp;
	int			i;

	i = -1;
	(void)le;
	arbre = NULL;
	path_and_word = get_actual_word(*line);
	buffer = ft_memalloc(sizeof(char) * 1024);
	creer_arbre(&arbre, path_and_word[0]);
	tmp = arbre;
	arbre = recherche(&arbre, path_and_word[1]);
	completion_tree(arbre, &buffer, 0);
	if (!buffer[0] && is_folder(path_and_word[1]))
		add_to_line(le, line, '/');
	else
		while (buffer[++i])
			add_to_line(le, line, buffer[i]);
	free_arbre(&tmp);
	free(buffer);
	free(path_and_word[0]);
	free(path_and_word[1]);
}
