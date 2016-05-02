/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 16:21:13 by rle-mino          #+#    #+#             */
/*   Updated: 2016/02/13 00:25:24 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				fpf(const char *format, ...)
{
	va_list		ap;
	size_t		k;

	va_start(ap, format);
	k = pf_print_line(ap, (char *)format);
	va_end(ap);
	return (k);
}
