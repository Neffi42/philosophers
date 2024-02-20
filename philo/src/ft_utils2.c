/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:47:49 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/20 09:51:43 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		return (NULL);
	r = malloc(x);
	if (!r)
		return (NULL);
	ft_memset(r, 0, x);
	return (r);
}
