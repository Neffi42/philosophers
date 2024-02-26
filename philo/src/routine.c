/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:43:53 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/26 15:10:54 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	simulation(t_philo *philo, long long time)
{
	if (check_start(philo) || print_state(philo))
		return (1);
	if (philo->last_meal && philo->rules.time_die < time - philo->last_meal)
		return (die(philo, time - philo->last_meal));
	if (philo->state == SLEEPING && ft_sleep(philo))
		return (1);
	else if (philo->state == THINKING)
	{
		pthread_mutex_lock(&(philo->mutex_fork));
		if (check_start(philo))
			return (1);
		philo->state = HAS_FORK;
	}
	else if (philo->state == HAS_FORK)
	{
		pthread_mutex_lock(philo->mutex_fork2);
		if (check_start(philo) || print_state(philo))
			return (1);
		philo->state = EATING;
	}
	else if (philo->state == EATING && eat(philo, time))
		return (1);
	return (0);
}

void	*routine(void *arg)
{
	t_philo		*philo;
	long long	time;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->mutex_start);
	pthread_mutex_unlock(philo->mutex_start);
	if (philo->rules.total_nb == 1)
		return (die(philo, philo->rules.time_die), NULL);
	if (philo->nb % 2 == 0)
		usleep(philo->rules.time_eat * 1000);
	if (!ft_ogettime(philo, &time))
		return (NULL);
	while (!simulation(philo, time))
		if (!ft_ogettime(philo, &time))
			return (NULL);
	return (NULL);
}
