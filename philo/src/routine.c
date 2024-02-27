/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:43:53 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/27 15:43:36 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	simulation(t_philo *philo, long long time)
{
	if (get_var(&(philo->shared->start)) == 0 || print_state(philo))
		return (1);
	if (philo->last_meal && philo->rules->time_die < time - philo->last_meal)
		return (die(philo, time - philo->last_meal));
	if (philo->state == SLEEPING)
	{
		if (sleeping(philo))
			return (1);
	}
	else if (philo->state == THINKING)
	{
		if (thinking(philo, time))
			return (1);
	}
	else if (philo->state == EATING)
	{
		if (eating(philo, time))
			return (1);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo		*philo;
	long long	time;

	philo = (t_philo *)arg;
	while (get_var(&(philo->shared->start)) == 0)
		usleep(1000);
	if (philo->id % 2 == 0)
		usleep(philo->rules->time_eat * 1000);
	if (get_time(philo, &time))
		return (set_var(&(philo->shared->start), 0), NULL);
	while (!simulation(philo, time))
		if (get_time(philo, &time))
			return (set_var(&(philo->shared->start), 0), NULL);
	return (NULL);
}
