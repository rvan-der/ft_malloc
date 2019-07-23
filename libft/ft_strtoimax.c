/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoimax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-der <rvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 21:00:50 by rvan-der          #+#    #+#             */
/*   Updated: 2018/10/04 20:29:51 by rvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			init_data(char *str, t_stoi_data *data)
{
	int				i;

	data->sign = 1;
	data->lower = NULL;
	data->endp = str;
	data->negative_limit = INTMAX_MIN;
	data->base = 0;
	if (!str)
		return (-1);
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		data->sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	data->endp += i;
	if (!(data->lower = ft_strlower(data->endp)))
		return (-1);
	if (data->sign == 1)
		data->negative_limit = INTMAX_MIN + 1;
	return (0);
}

static int			check_input(t_stoi_data *data, int base)
{
	if (!data->lower || !data->lower[0])
		return (-1);
	if (!base)
	{
		base = 10;
		if (data->lower[0] == '0')
		{
			base = 8;
			if (data->lower[1] && data->lower[1] == 'x' &&\
				data->lower[2] && ft_strnchr(BASE_STR, data->lower[2], 16))
				base = 16;
		}
	}
	if (base == 16 && data->lower[0] == '0' && data->lower[1] && \
		data->lower[1] == 'x')
	{
		free(data->lower);
		data->endp += 2;
		data->lower = ft_strlower(data->endp);
	}
	if (base < 2 || base > 36 || !data->lower[0] ||\
		!ft_strnchr(BASE_STR, data->lower[0], base))
		return (-1);
	data->base = base;
	return (0);
}

static intmax_t		get_digit(char c, int base)
{
	intmax_t		value;

	value = -1;
	while (BASE_STR[++value] && value < base)
		if (BASE_STR[value] == c)
			return (value);
	return (-1);
}

intmax_t			ret_error(int err_val, char **endptr, \
								char *str, t_stoi_data data)
{
	int				i;

	if (endptr)
	{
		*endptr = str;
		if (err_val == ERANGE)
		{
			i = 0;
			while (data.lower[i] && ft_strnchr(BASE_STR, data.lower[i], \
					data.base))
				i++;
			*endptr = data.endp + i;
		}
	}
	if (data.lower)
		free(data.lower);
	errno = err_val;
	if (err_val == ERANGE && data.sign == -1)
		return ((intmax_t)INTMAX_MIN);
	if (err_val == ERANGE && data.sign == 1)
		return ((intmax_t)INTMAX_MAX);
	return (0);
}

intmax_t			ft_strtoimax(const char *restrict str, \
									char **restrict endptr, int base)
{
	int				i;
	intmax_t		nb;
	intmax_t		digit;
	t_stoi_data		data;

	if (init_data((char*)str, &data) == -1)
		return (ret_error(EINVAL, endptr, (char*)str, data));
	if (check_input(&data, base) == -1)
		return (ret_error(EINVAL, endptr, (char*)str, data));
	nb = 0;
	i = -1;
	while ((digit = get_digit(data.lower[++i], data.base)) > -1)
	{
		if (-nb < data.negative_limit / data.base || \
			-digit < data.negative_limit + nb * 10)
			return (ret_error(ERANGE, endptr, (char*)str, data));
		nb = nb * data.base + digit;
	}
	if (endptr)
		*endptr = data.endp + i;
	digit = data.sign;
	free(data.lower);
	return (nb * digit);
}
