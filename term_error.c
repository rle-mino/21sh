/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 05:23:21 by ishafie           #+#    #+#             */
/*   Updated: 2016/04/26 05:23:50 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"

void	malloc_handling(void)
{
	ft_putstr_fd("Allocation failure, exiting...\n", 2);
	exit(-1);
}

void	message_handling(void)
{
	ft_putstr_fd("Environnement failure, exiting...\n", 2);
	exit(-1);
}
