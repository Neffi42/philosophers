/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:43:53 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/21 14:55:15 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_timeval	tv;
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (gettimeofday(&tv, NULL))
		return (error(FUNCTION, "gettimeofday"), NULL);
	printf("time: %ld\t%u is waiting\n", tv.tv_sec, philo->nb);
	return (NULL);
}
