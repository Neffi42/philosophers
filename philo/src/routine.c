/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:43:53 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/22 15:09:06 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	change_state(t_philo *philo, t_state state, char *message)
{
	t_timeval	tv;

	philo->state = state;
	if (gettimeofday(&tv, NULL))
		return (error(FUNCTION, "gettimeofday"));
	pthread_mutex_lock(philo->mutex_write);
	printf("[%ld] %u %s\n", (tv.tv_sec * 1000 + tv.tv_usec / 1000),
		philo->nb, message);
	pthread_mutex_unlock(philo->mutex_write);
	return (0);
}

static int	simulation(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_is_dead);
		if (philo->is_dead)
			return (pthread_mutex_unlock(philo->mutex_is_dead), 1);
	pthread_mutex_unlock(philo->mutex_is_dead);
	if (philo->state == EATING && change_state(philo, EATING, "is eating"))
			return (1);
	else if (philo->state == SLEEPING)
		if (change_state(philo, SLEEPING, "is sleeping"))
			return (1);
	else if (philo->state == THINKING)
		if (change_state(philo, THINKING, "is thinking"))
			return (1);
	return (0);
}

void	*routine(void *arg)
{
	t_timeval	tv;
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (gettimeofday(&tv, NULL))
		return (error(FUNCTION, "gettimeofday"), NULL);
	pthread_mutex_lock(philo->mutex_start);
	pthread_mutex_unlock(philo->mutex_start);
	while (!simulation(philo))
		;
	return (NULL);
}

/**
 * has taken a fork
 * is eating
 * is sleeping
 * is thinking
 * died
 */
