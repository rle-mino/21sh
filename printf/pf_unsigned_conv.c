/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_unsigned_conv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 10:43:04 by rle-mino          #+#    #+#             */
/*   Updated: 2016/02/07 22:12:36 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				unsigned_conv(t_struct data, va_list ap, int lower)
{
	if (data.clong == 0 && lower == 1)
		return (unsigned_conv_noclong(data, va_arg(ap, unsigned int)));
	if (data.clong & 1 && lower == 1)
		return (unsigned_conv_hh(data, va_arg(ap, unsigned int)));
	if (data.clong & 2 || lower == 0)
		return (unsigned_conv_ll(data, va_arg(ap, unsigned long long)));
	if (data.clong & 4)
		return (unsigned_conv_h(data, va_arg(ap, unsigned int)));
	if (data.clong & 8)
		return (unsigned_conv_l(data, va_arg(ap, unsigned long)));
	if (data.clong & 16)
		return (unsigned_conv_j(data, va_arg(ap, uintmax_t)));
	if (data.clong & 32)
		return (unsigned_conv_z(data, va_arg(ap, size_t)));
	return (0);
}
