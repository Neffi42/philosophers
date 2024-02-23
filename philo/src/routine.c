/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:43:53 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/23 13:03:39 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	change_state(t_philo *philo, t_state state)
{
	t_timeval	tv;

	philo->state = state;
	if (gettimeofday(&tv, NULL))
		return (error(FUNCTION, "gettimeofday"));
	pthread_mutex_lock(philo->mutex_write);
	printf("[%ld] %u %s\n", (tv.tv_sec * 1000 + tv.tv_usec / 1000), philo->nb,
		find_message(state));
	pthread_mutex_unlock(philo->mutex_write);
	return (0);
}

static int	simulation(t_philo *philo)
{
	pthread_mutex_lock(philo->start);
		if (!philo->start)
			return (pthread_mutex_unlock(philo->mutex_start), 1);
	pthread_mutex_unlock(philo->mutex_start);
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
	while (!simulation(philo))
		;
	return (NULL);
}
