/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:43:53 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/28 14:03:46 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	eating(t_philo *philo)
{
	if (print_state(philo)
		|| get_time(philo, &philo->last_meal)
		|| ft_usleep(philo, philo->rules->time_eat))
		return (1);
	set_var(&(philo->fork), 0);
	if (is_philo_dead(philo))
		return (1);
	set_var(philo->fork2, 0);
	if (is_philo_dead(philo))
		return (1);
	if (++(philo->nb_meals) == philo->rules->total_eat)
		set_var(&philo->finished, 1);
	return (philo->state = SLEEPING, 0);
}

static int	sleeping(t_philo *philo)
{
	print_state(philo);
	ft_usleep(philo, philo->rules->time_sleep);
	return (philo->state = THINKING, 0);
}

static int	get_fork(t_philo *philo, t_fork *fork)
{
	while (get_var(fork) != 0)
		if (ft_usleep(philo, 100))
			return (1);
	(set_var(fork, philo->id), philo->state = HAS_FORK);
	if (is_philo_dead(philo) || print_state(philo))
		return (1);
	return (0);
}

static int	thinking(t_philo *philo)
{
	if (print_state(philo))
		return (1);
	if (get_fork(philo, &(philo->fork)) || get_fork(philo, philo->fork2))
		return (1);
	return (philo->state = EATING, 0);
}

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (get_var(&(philo->vars->start)) == 0)
		usleep(10);
	if (!(philo->id % 2))
		if (usleep(1000))
			return (NULL);
	if (get_time(philo, &philo->last_meal) || is_philo_dead(philo))
		return (NULL);
	while (!thinking(philo) && !eating(philo) && !sleeping(philo))
		;
	return (NULL);
}
