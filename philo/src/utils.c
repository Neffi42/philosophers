/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:34:03 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/26 10:29:00 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(char *message, char *el)
{
	if (el)
		write(STDERR_FILENO, el, ft_strlen(el));
	write(STDERR_FILENO, message, ft_strlen(message));
	return (1);
}

static void	destroy_mutexes(t_philo *philos, int total_nb)
{
	int	i;

	i = -1;
	while (++i < total_nb)
		if (philos[i].nb != 0)
			pthread_mutex_destroy(&(philos[i].mutex_fork));
}

static void	destroy_threads(t_philo *philos, int total_nb)
{
	int	i;

	i = -1;
	while (++i < total_nb)
		if (philos[i].thread)
			pthread_join(philos[i].thread, NULL);
}

int	destroy(t_philo *philos, int total_nb)
{
	if (!philos)
		return (1);
	destroy_threads(philos, total_nb);
	destroy_mutexes(philos, total_nb);
	pthread_mutex_destroy(philos->mutex_start);
	pthread_mutex_destroy(philos->mutex_write);
	pthread_mutex_destroy(philos->mutex_finished);
	return (free(philos), 1);
}
