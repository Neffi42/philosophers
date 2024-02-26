/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:35:39 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/26 15:11:06 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	die(t_philo *philo, long long time)
{
	philo->state = DEAD;
	usleep(time);
	if (check_start(philo))
		return (1);
	sim_error(philo, NULL, NULL);
	print_state(philo);
	return (1);
}

int	eat(t_philo *philo, long long time)
{
	philo->last_meal = time;
	if (philo->rules.time_eat > philo->rules.time_die)
		usleep(philo->rules.time_die * 1000);
	else
		usleep(philo->rules.time_eat * 1000);
	if (check_start(philo))
		return (1);
	pthread_mutex_unlock(&(philo->mutex_fork));
	pthread_mutex_unlock(philo->mutex_fork2);
	philo->state = SLEEPING;
	if (philo->rules.time_eat > philo->rules.time_die)
		return (die(philo, 0));
	if (++(philo->nb_meals) != philo->rules.total_eat)
		return (0);
	(pthread_mutex_lock(philo->mutex_finished), *(philo->finished) += 1);
	return (pthread_mutex_unlock(philo->mutex_finished), 0);
}

int	ft_sleep(t_philo *philo)
{
	philo->state = THINKING;
	if (philo->rules.time_eat + philo->rules.time_sleep > philo->rules.time_die)
		return (die(philo,
				1000 * (philo->rules.time_die - philo->rules.time_eat)));
	usleep(philo->rules.time_sleep * 1000);
	if (check_start(philo))
		return (1);
	return (0);
}

static void	unlock_all(t_philo *philo)
{
	if (philo->state == HAS_FORK || philo->state == EATING)
		pthread_mutex_unlock(&(philo->mutex_fork));
	if (philo->state == EATING)
		pthread_mutex_unlock(philo->mutex_fork2);
	pthread_mutex_unlock(philo->mutex_start);
}

int	check_start(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_start);
	if (*(philo->start) == 0)
		return (unlock_all(philo), 1);
	return (pthread_mutex_unlock(philo->mutex_start), 0);
}
