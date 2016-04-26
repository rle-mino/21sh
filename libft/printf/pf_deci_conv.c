/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_deci_conv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 16:07:40 by rle-mino          #+#    #+#             */
/*   Updated: 2016/02/08 01:33:36 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				deci_conv(t_struct data, va_list ap)
{
	if (data.clong == 0)
		return (deci_conv_noclong(data, va_arg(ap, int)));
	if (data.clong & 1)
		return (deci_conv_hh(data, (char)va_arg(ap, int)));
	if (data.clong & 2 || data.clong & 16 || data.clong & 32)
		return (deci_conv_ll(data, va_arg(ap, long long)));
	if (data.clong & 4)
		return (deci_conv_h(data, va_arg(ap, int)));
	if (data.clong & 8)
		return (deci_conv_l(data, va_arg(ap, long)));
	return (0);
}
