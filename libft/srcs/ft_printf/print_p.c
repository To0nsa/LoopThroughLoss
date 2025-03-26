/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:10:58 by nlouis            #+#    #+#             */
/*   Updated: 2025/02/16 22:47:20 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_with_padding(t_fmt *fmt, char *str, t_pf *pf)
{
	int		padding;
	int		len;

	len = ft_strlen(str);
	if (fmt->precision > len)
	{
		str = handle_precision_p(fmt, str, &len, pf);
		if (!str)
			return ;
	}
	padding = handle_width(fmt, len);
	handle_space_flag_p(pf, &padding);
	if (pf->write_error != 0)
		return ;
	handle_minus_flag_p(str, padding, pf);
	if (pf->write_error != 0)
		return ;
	print_right_aligned_p(fmt, str, padding, pf);
	if (pf->write_error != 0)
		return ;
	if (str != NULL)
		free(str);
}

static char	*handle_null_ptr(t_pf *pf)
{
	char	*str;

	str = ft_strdup("(nil)");
	if (str == NULL)
		pf->malloc_error = 1;
	return (str);
}

static char	*convert_ptr_to_hex(void *ptr, t_pf *pf)
{
	char	*str;
	char	*new_str;

	str = ft_itoa_base((unsigned long long)ptr, 16, 0);
	if (str == NULL)
	{
		pf->malloc_error = 1;
		return (NULL);
	}
	new_str = ft_strjoin("0x", str);
	free(str);
	if (new_str == NULL)
		pf->malloc_error = 1;
	return (new_str);
}

void	format_and_print_p(t_fmt *fmt, va_list *args, t_pf *pf)
{
	void	*ptr;
	char	*str;

	ptr = va_arg(*args, void *);
	if (!ptr)
		str = handle_null_ptr(pf);
	else
		str = convert_ptr_to_hex(ptr, pf);
	if (str == NULL)
		return ;
	print_with_padding(fmt, str, pf);
	if (pf->write_error != 0)
		return ;
}
