/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_call_printer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 11:29:48 by rle-mino          #+#    #+#             */
/*   Updated: 2016/02/26 10:27:11 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		unicode(va_list ap, char conv)
{
	if (conv == 'C')
		return (pf_putcharuni(va_arg(ap, wchar_t)));
	else if (conv == 'S')
		return (pf_putstruni(va_arg(ap, wchar_t*)));
	if (conv == 'b')
		return (pf_retbin(va_arg(ap, size_t)));
	return (0);
}

int		noflag_no_clong(va_list ap, char conv)
{
	if (conv == 's')
		return (pf_putstr(va_arg(ap, char*)));
	if (conv == 'c')
		return (pf_putchar(va_arg(ap, int)));
	if (conv == 'd' || conv == 'i')
		return (pf_retdeci_noclong(va_arg(ap, int), 1));
	if (conv == 'x')
		return (pf_rethexa_noclong(va_arg(ap, unsigned int), 1));
	if (conv == 'X')
		return (pf_rethexa_noclong(va_arg(ap, unsigned int), 0));
	if (conv == 'o')
		return (pf_retoctal_noclong(va_arg(ap, unsigned int), 1));
	if (conv == 'O')
		return (pf_retoctal_l(va_arg(ap, unsigned long), 1));
	if (conv == 'u')
		return (pf_retunsigned_noclong(va_arg(ap, unsigned int), 1));
	if (conv == 'U')
		return (pf_retunsigned_l(va_arg(ap, unsigned long), 1));
	if (conv == 'D')
		return (pf_retdeci_ll(va_arg(ap, long long), 1));
	if (conv == 'p')
		return (pf_retmem_noclong(va_arg(ap, size_t), 1));
	else
		return (unicode(ap, conv));
	return (0);
}

int		pf_print_var(t_struct data, char conv, va_list ap)
{
	if (data.flag == 0 && data.clong == 0 && data.prec == 0 && data.min == 0)
		return (noflag_no_clong(ap, conv));
	else if (conv == '%')
		return (percent_conv(data));
	else if (conv == 'x' || conv == 'X')
		return (hexa_conv(data, ap, (conv == 'x' ? 1 : 0)));
	else if (conv == 's' || conv == 'S')
		return (string_conv(data, ap, conv == 's' ? 1 : 0));
	else if (conv == 'c' || conv == 'C')
		return (char_conv(data, ap, conv == 'c' ? 1 : 0));
	else if (conv == 'o' || conv == 'O')
		return (octal_conv(data, ap, conv == 'o' ? 1 : 0));
	else if (conv == 'd' || conv == 'i')
		return (deci_conv(data, ap));
	else if (conv == 'D')
		return (deci_conv_ll(data, va_arg(ap, long long)));
	else if (conv == 'u' || conv == 'U')
		return (unsigned_conv(data, ap, conv == 'U' ? 0 : 1));
	else if (conv == 'p')
		return (mem_conv(data, ap));
	return (0);
}
