/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:15:19 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/26 11:40:59 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	eat(t_philo *philo)
{
	t_timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (error(FUNCTION, "gettimeofday"));
	philo->last_meal = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (0);
}

static int	die(t_philo *philo, long long time)
{
	usleep(time);
	sim_error(philo, NULL, NULL);
	change_state(philo, DEAD);
	return (1);
}

static int	ft_sleep(t_philo *philo, long long time)
{
	if (time - philo->last_meal - philo->rules.time_eat >  philo->rules.time_die)
		return (1);
	usleep(time);
	sim_error(philo, NULL, NULL);
	change_state(philo, DEAD);

	usleep(philo->rules.time_sleep * 1000);
	return (0);
}


int	simulation(t_philo *philo, long long time)
{
	pthread_mutex_lock(philo->mutex_start);
	if (!philo->start)
		return (pthread_mutex_unlock(philo->mutex_start), 1);
	pthread_mutex_unlock(philo->mutex_start);
	if (philo->rules.time_die < time - philo->last_meal)
		return (die(philo, time - philo->last_meal));
	else if (change_state(philo, find_new_state(philo->state)))
		return (1);
	if (philo->state == SLEEPING)
		ft_sleep(philo, time);
	else if (philo->state == THINKING)
		pthread_mutex_lock(&(philo->mutex_fork));
	else if (philo->state == HAS_FORK)
		pthread_mutex_lock(philo->mutex_fork2);
	else if (philo->state == EATING)
		eat(philo);
	if (philo->state == DEAD)
		return (die(philo, 0));
	return (0);
}
