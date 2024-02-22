/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:43:53 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/22 11:32:14 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	change_state(t_philo *philo, t_state state, char *message)
{
	t_timeval	tv;

	philo->state = state;
	if (gettimeofday(&tv, NULL))
		return (error(FUNCTION, "gettimeofday"));
	pthread_mutex_lock(&(philo->args->write));
	printf("[%ld] %u %s\n", (tv.tv_sec * 1000 + tv.tv_usec / 1000),
		philo->nb, message);
	pthread_mutex_unlock(&(philo->args->write));
	return (0);
}

void	*routine(void *arg)
{
	t_timeval	tv;
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (gettimeofday(&tv, NULL))
		return (error(FUNCTION, "gettimeofday"), NULL);
	pthread_mutex_lock(&(philo->args->start));
	pthread_mutex_unlock(&(philo->args->start));
	change_state(philo, philo->state, "has taken a fork");
	return (NULL);
}

/**
 * has taken a fork
 * is eating
 * is sleeping
 * is thinking
 * died
 */
