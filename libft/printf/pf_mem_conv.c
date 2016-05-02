/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_mem_conv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 22:39:59 by rle-mino          #+#    #+#             */
/*   Updated: 2016/02/08 02:03:00 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		mem_conv(t_struct data, va_list ap)
{
	if (data.flag == 0 && data.min == 0 && data.prec == 0)
		return (pf_retmem_noclong(va_arg(ap, size_t), 1));
	return (mem_conv_noclong(data, va_arg(ap, size_t)));
}
