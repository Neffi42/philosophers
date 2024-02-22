/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:23:48 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/22 16:45:53 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philo(t_philo *philo, t_shared *shared, t_args args)
{
	if ((!(args.total_nb % 2) && !(philo->nb % 2))
		|| (args.total_nb % 2 && philo->nb % 2))
		philo->state = EATING;
	else
		philo->state = THINKING;
	philo->thread = 0;
	philo->mutex_is_dead = &(shared->mutex_is_dead);
	philo->mutex_write = &(shared->mutex_write);
	philo->mutex_start = &(shared->mutex_start);
	philo->is_dead = &(shared->is_dead);
	philo->args.time_die = args.time_die;
	philo->args.time_eat = args.time_eat;
	philo->args.time_sleep = args.time_sleep;
	philo->args.total_eat = args.total_eat;
	philo->args.total_nb = args.total_nb;
}

int	init_philos(t_philo *philos, t_shared *shared, t_args args)
{
	unsigned int	i;

	i = 0;
	while (i < args.total_nb)
		philos[i++].nb = 0;
	i = 0;
	while (i < args.total_nb)
	{
		(init_philo(&philos[i], shared, args), philos[i].nb = i + 1);
		if (pthread_mutex_init(&(philos[i].fork), NULL))
			return (error(FUNCTION, "pthread_mutex_init"),
				destroy(philos, i));
		if (pthread_create(&(philos[i].thread), NULL, routine, &philos[i]))
			return (error(FUNCTION, "pthread_create"), destroy(philos, i));
		if (i > 0)
			philos[i].fork2 = &(philos[i - 1].fork);
		if (i + 1 == args.total_nb)
			philos[0].fork2 = &(philos[i].fork);
		i++;
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
	if (pthread_mutex_init(&(shared->mutex_is_dead), NULL))
		return (pthread_mutex_destroy(&(shared->mutex_start)),
			pthread_mutex_destroy(&(shared->mutex_write)),
			error(FUNCTION, "pthread_mutex_init"));
	return (shared->is_dead = 0, 0);
}
