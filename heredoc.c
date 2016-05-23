/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 13:53:03 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/19 16:00:46 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"

t_word				*rdwr_in_heredocs(char *in_heredoc)
{
	static t_word		*here_path = NULL;
	static char			basic_path[16] = "/tmp/.21hdocsid";
	static int			id = 0;
	t_word				*tmp;

	if (!here_path && in_heredoc)
	{
		here_path = ft_memalloc(sizeof(t_word));
		here_path->word = ft_strjoin(basic_path, ft_itoa(id++));
		tmp = here_path;
		get_heredocs_add(tmp);
	}
	else if ((tmp = here_path) && in_heredoc && (void*)in_heredoc != here_path)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_memalloc(sizeof(t_word));
		tmp = tmp->next;
		tmp->word = ft_strjoin(basic_path, ft_itoa(id++));
	}
	if (in_heredoc && (void*)in_heredoc != here_path)
		write_here_in_file(tmp, in_heredoc);
	if ((void*)in_heredoc == here_path)
		here_path = clear_words(&here_path, &id);
	return (here_path);
}

static void			add_to_here(t_word **here, char *eoh)
{
	t_word		*tmp;

	if (!*here)
	{
		*here = ft_memalloc(sizeof(t_word));
		(*here)->word = ft_strdup(eoh);
		return ;
	}
	else
	{
		tmp = *here;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_memalloc(sizeof(t_word));
		tmp = tmp->next;
		tmp->word = ft_strdup(eoh);
	}
}

static void			get_eoh(t_line *line, t_word **here)
{
	char	buff[1024];
	int		i;

	i = 0;
	if (line->next && line->next->next)
		line = line->next->next;
	if (line && line->c == ' ')
		line = line->next;
	ft_bzero(buff, sizeof(buff));
	while (line && line->c != ' ')
	{
		buff[i] = line->c;
		i++;
		line = line->next;
	}
	add_to_here(here, buff);
}

static t_word		*get_heredocs(t_line *line)
{
	t_word	*here;

	here = NULL;
	while (line)
	{
		if (line->c == '<' && line->next && line->next->c == '<')
			get_eoh(line, &here);
		if (line)
			line = line->next;
	}
	return (here);
}

void				prepare_heredoc(t_le *le, t_line *line)
{
	t_word	*heredocs;
	void	*tmp;
	char	*in_heredoc;

	heredocs = get_heredocs(line);
	tmp = le->line;
	le->sig = 0;
	signal(SIGINT, stop_heredoc);
	while (heredocs)
	{
		le->line = NULL;
		le->line = edit_line_heredoc(le, heredocs->word, 0);
		if (le->sig)
			return (ignore_heredoc(le, tmp));
		in_heredoc = to_string(le->line, NORMAL);
		clear_line(le->line);
		rdwr_in_heredocs(in_heredoc);
		heredocs = heredocs->next;
	}
	le->line = tmp;
}
