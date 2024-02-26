/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:23:48 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/26 10:49:16 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philo(t_philo *philo, t_shared *shared, t_rules rules)
{
	philo->rules.time_die = rules.time_die;
	philo->rules.time_eat = rules.time_eat;
	philo->rules.time_sleep = rules.time_sleep;
	philo->rules.total_eat = rules.total_eat;
	philo->rules.total_nb = rules.total_nb;
	philo->state = EATING;
	philo->thread = 0;
	philo->last_meal = 0;
	philo->start = &(shared->start);
	philo->finished = &(shared->finished);
	philo->mutex_write = &(shared->mutex_write);
	philo->mutex_start = &(shared->mutex_start);
	philo->fork = 0;
}

int	init_philos(t_philo *philos, t_shared *shared, t_rules rules)
{
	int	i;

	i = -1;
	while (++i < rules.total_nb)
		philos[i].nb = 0;
	i = -1;
	while (++i < rules.total_nb)
	{
		(init_philo(&philos[i], shared, rules), philos[i].nb = i + 1);
		if (pthread_mutex_init(&(philos[i].mutex_fork), NULL))
			return (error(FUNCTION, "pthread_mutex_init"),
				destroy(philos, i));
		if (pthread_create(&(philos[i].thread), NULL, routine, &philos[i]))
			return (error(FUNCTION, "pthread_create"), destroy(philos, i));
		philos[i].fork2 = &(philos[(i + 1) % rules.total_nb].fork);
	}
	return (0);
}

int	init_shared(t_shared *shared)
{
	if (pthread_mutex_init(&(shared->mutex_start), NULL))
		return (error(FUNCTION, "pthread_mutex_init"));
	if (pthread_mutex_init(&(shared->mutex_write), NULL))
		return (pthread_mutex_destroy(&(shared->mutex_start)),
			error(FUNCTION, "pthread_mutex_init"));
	if (pthread_mutex_init(&(shared->mutex_finished), NULL))
		return (pthread_mutex_destroy(&(shared->mutex_start)),
			pthread_mutex_destroy(&(shared->mutex_write)),
			error(FUNCTION, "pthread_mutex_init"));
	return (shared->finished = 0, 0);
}
