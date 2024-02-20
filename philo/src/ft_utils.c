/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 19:11:26 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/20 13:05:02 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	ft_nbrlen(ssize_t	nbr)
{
	size_t	count;

	count = 1;
	while (nbr / 10)
	{
		count++;
		nbr /= 10;
	}
	return (count);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
		i++;
	return (i);
}

char	*ft_uitoa(unsigned int n)
{
	unsigned long	nbr;
	size_t			count;
	char			*str_n;

	nbr = n;
	count = ft_nbrlen(nbr);
	str_n = malloc((count + 1) * sizeof(char));
	if (!str_n)
		return (NULL);
	str_n[count--] = '\0';
	if (!nbr)
		str_n[count--] = nbr + '0';
	while (nbr)
	{
		str_n[count--] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (!count)
		str_n[count] = '-';
	return (str_n);
}

unsigned int	ft_atoui(const char *nptr)
{
	unsigned int	n;

	n = 0;
	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			return (0);
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
		n = n * 10 + (*(nptr++) - '0');
	return (n);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - s2[i]);
		i++;
	}
	return (0);
}
