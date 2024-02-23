/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:43:53 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/23 14:04:28 by abasdere         ###   ########.fr       */
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

static void	eat(t_philo *philo)
{
	t_timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (error(FUNCTION, "gettimeofday"), NULL);
	philo->last_meal = tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

static int	simulation(t_philo *philo, size_t current_time)
{
	pthread_mutex_lock(philo->start);
	if (!philo->start)
		return (pthread_mutex_unlock(philo->mutex_start), 1);
	pthread_mutex_unlock(philo->mutex_start);
	if (philo->args.time_die < current_time - philo->last_meal)
		philo->state = DEAD;
	else if (change_state(philo, find_new_state(philo->state)))
		return (1);
	if (philo->state == DEAD)
	{
			pthread_mutex_lock(philo->mutex_finished);
			*(philo->finished) = philo->args.total_nb;
			return (pthread_mutex_unlock(philo->mutex_finished), 1);
	}
	else if (philo->state == SLEEPING)
		usleep(philo->args.time_sleep * 1000);
	else if (philo->state == THINKING)
		pthread_mutex_lock(&(philo->mutex_fork));
	else if (philo->state == HAS_FORK)
		pthread_mutex_lock(philo->mutex_fork2);
	else if (philo->state == EATING)
	return (0);
}

void	*routine(void *arg)
{
	t_timeval	tv;
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (gettimeofday(&tv, NULL))
		return (error(FUNCTION, "gettimeofday"), NULL);
	philo->last_meal = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	while (!simulation(philo, tv.tv_sec * 1000 + tv.tv_usec / 1000))
		if (gettimeofday(&tv, NULL))
			return (error(FUNCTION, "gettimeofday"), NULL);
	return (NULL);
}
