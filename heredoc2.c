/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 17:24:22 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/19 15:49:06 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"

void		ignore_heredoc(t_le *le, void *tmp)
{
	le->sig = 0;
	le->line = tmp;
	clear_line(le->line);
	le->line = ft_memalloc(sizeof(t_line));
	le->line->is_orig = 1;
	signal(SIGINT, restart_prompt);
}

t_word		*clear_words(t_word **word, int *id)
{
	t_word	*tmp;

	while (*word)
	{
		tmp = *word;
		free((*word)->word);
		*word = (*word)->next;
		free(tmp);
	}
	*id = 0;
	return (NULL);
}

void		write_here_in_file(t_word *tmp, char *in_heredoc)
{
	int		fd;

	if ((fd = open(tmp->word, O_WRONLY | O_CREAT | O_TRUNC, 0644)) > 0
																&& in_heredoc)
	{
		ft_putstr_fd(in_heredoc, fd);
		close(fd);
	}
}
