/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 19:11:26 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/26 10:12:28 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	count_chars(int n)
{
	size_t	chars;

	chars = 0;
	if (n == -2147483648)
		return (11);
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		chars++;
	}
	while (n > 0)
	{
		n /= 10;
		chars++;
	}
	return (chars);
}

static int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char	*ft_itoa(int n)
{
	char	*r;
	int		sign;
	size_t	i;

	sign = 0;
	if (n < 0)
		sign = 1;
	i = count_chars(n);
	r = (char *) ft_calloc(i + 1, sizeof(char));
	if (!r)
		return (NULL);
	while (i-- > 0)
	{
		r[i] = ft_abs(n % 10) + '0';
		n /= 10;
	}
	if (sign)
		r[0] = '-';
	return (r);
}

static int	ft_isspace(char c)
{
	return (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v');
}

int	ft_atoi(const char *nptr)
{
	int	r;
	int	sign;

	r = 0;
	sign = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr)
	{
		if (*nptr < '0' || *nptr > '9')
			return (r * sign);
		r *= 10;
		r += *nptr - '0';
		nptr++;
	}
	return (r * sign);
}
