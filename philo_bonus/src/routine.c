/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:43:53 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/29 14:52:34 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	get_fork(t_philo *philo)
{
	sem_wait(philo->sems->forks);
	if (is_philo_dead(philo) || print_state(philo, HAS_FORK))
		return (1);
	return (0);
}

static int	eating(t_philo *philo)
{
	if (get_fork(philo) || get_fork(philo))
		return (1);
	if (print_state(philo, EATING)
		|| get_time(philo, &philo->last_meal)
		|| ft_usleep(philo, philo->rules->time_eat))
		return (1);
	sem_post(philo->sems->forks);
	if (is_philo_dead(philo))
		return (1);
	sem_post(philo->sems->forks);
	if (is_philo_dead(philo))
		return (1);
	if (philo->rules->total_meals)
	{
		sem_wait(philo->sems->meals);
		if (is_philo_dead(philo))
			return (sem_post(philo->sems->meals), 1);
		if (++(philo->nb_meals) == philo->rules->total_meals)
			philo->sems->nb_meals++;
		sem_post(philo->sems->meals);
	}
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
	(sem_wait(philo->sems->run), sem_post(philo->sems->run));
	if (philo->rules->total_nb == 1)
		return (one_philo(philo));
	if (philo->id % 2)
		usleep(10000);
	if (get_time(philo, &philo->last_meal) || is_philo_dead(philo))
		return (NULL);
	while (!thinking(philo) && !eating(philo) && !sleeping(philo))
		;
	return (NULL);
}
