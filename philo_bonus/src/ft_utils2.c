/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:47:49 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/28 22:25:20 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

static void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = s;
	i = -1;
	while (++i < n)
		*p++ = c;
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*r;
	size_t	x;

	x = nmemb * size;
	if (size != 0 && x / size != nmemb)
		return (error(FCT, "ft_calloc"), NULL);
	r = malloc(x);
	if (!r)
		return (error(FCT, "malloc"), NULL);
	ft_memset(r, 0, x);
	return (r);
}
