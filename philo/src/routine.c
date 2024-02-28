/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:43:53 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/28 21:56:15 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_fork(t_philo *philo, t_fork *fork)
{
	while (get_var(fork) != 0)
		if (ft_usleep(philo, 100))
			return (1);
	set_var(fork, philo->id);
	if (is_philo_dead(philo) || print_state(philo, HAS_FORK))
		return (1);
	return (0);
}

static int	eating(t_philo *philo)
{
	if (get_fork(philo, &(philo->fork)) || get_fork(philo, philo->fork2))
		return (1);
	if (print_state(philo, EATING)
		|| get_time(philo, &philo->last_meal)
		|| ft_usleep(philo, philo->rules->time_eat))
		return (1);
	set_var(&(philo->fork), 0);
	if (is_philo_dead(philo))
		return (1);
	set_var(philo->fork2, 0);
	if (is_philo_dead(philo))
		return (1);
	if (philo->rules->total_meals)
		if (++(philo->nb_meals) == philo->rules->total_meals)
			incr_var(&philo->vars->meals);
	return (0);
}

static int	sleeping(t_philo *philo)
{
	if (print_state(philo, SLEEPING))
		return (1);
	return (ft_usleep(philo, philo->rules->time_sleep));
}

static int	thinking(t_philo *philo)
{
	if (print_state(philo, THINKING))
		return (1);
	return (0);
}

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (get_var(&(philo->vars->run)) == 0)
		usleep(10);
	if (philo->id % 2)
		if (usleep(10000))
			return (NULL);
	pthread_mutex_lock(&philo->vars->meals.mutex);
	if (get_time(philo, &philo->last_meal))
		return (pthread_mutex_unlock(&philo->vars->meals.mutex), NULL);
	pthread_mutex_unlock(&philo->vars->meals.mutex);
	if (is_philo_dead(philo))
		return (NULL);
	while (!thinking(philo) && !eating(philo) && !sleeping(philo))
		;
	return (NULL);
}
