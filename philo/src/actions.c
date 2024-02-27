/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:35:39 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/27 15:40:44 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	die(t_philo *philo, long long time)
{
	philo->state = DEAD;
	usleep(time);
	if (get_var(&(philo->shared->start)) == 0 || print_state(philo))
		return (1);
	set_var(&(philo->shared->start), 0);
	return (1);
}

int	eating(t_philo *philo, long long time)
{
	philo->last_meal = time;
	if (philo->rules->time_eat > philo->rules->time_die)
		die(philo, philo->rules->time_die * 1000);
	else
		usleep(philo->rules->time_eat * 1000);
	if (get_var(&(philo->shared->start)) == 0)
		return (1);
	set_var(&(philo->fork), 0);
	if (get_var(&(philo->shared->start)) == 0)
		return (1);
	set_var(philo->fork2, 0);
	if (get_var(&(philo->shared->start)) == 0)
		return (1);
	philo->state = SLEEPING;
	if (++(philo->nb_meals) == philo->rules->total_eat)
		set_var(&(philo->finished), 1);
	return (0);
}

int	sleeping(t_philo *philo)
{
	philo->state = THINKING;
	if (philo->rules->time_eat + philo->rules->time_sleep
		> philo->rules->time_die)
		return (die(philo,
				1000 * (philo->rules->time_die - philo->rules->time_eat)));
	usleep(philo->rules->time_sleep * 1000);
	if (get_var(&(philo->shared->start)) == 0)
		return (1);
	return (0);
}

static int	get_fork(t_philo *philo, t_fork *fork, long long time)
{
	long long	new_time;

	while (get_var(fork) != 0)
	{
		if (get_var(&(philo->shared->start)) == 0 || get_time(philo, &new_time)
			|| new_time - time > philo->rules->time_die)
			return (die(philo, 0));
		usleep(1000);
	}
	(set_var(fork, philo->id), philo->state = HAS_FORK);
	if (get_var(&(philo->shared->start)) == 0 || print_state(philo))
		return (1);
	return (0);
}

int	thinking(t_philo *philo, long long time)
{
	if (get_fork(philo, &(philo->fork), time) || get_time(philo, &time))
		return (1);
	if (get_fork(philo, philo->fork2, time))
		return (1);
	return (philo->state = EATING, 0);
}
