/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:34:03 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/28 15:16:40 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(char *message, char *el)
{
	if (el)
		write(STDERR_FILENO, el, ft_strlen(el));
	if (message)
		write(STDERR_FILENO, message, ft_strlen(message));
	return (1);
}

int	destroy(t_philo *philos, int total_nb)
{
	int	i;

	i = -1;
	while (++i < total_nb)
		if (philos[i].thread)
			pthread_join(philos[i].thread, NULL);
	i = -1;
	while (++i < total_nb)
		pthread_mutex_destroy(&philos[i].fork.mutex);
	pthread_mutex_destroy(&philos->vars->run.mutex);
	pthread_mutex_destroy(&philos->vars->write);
	pthread_mutex_destroy(&philos->vars->meals.mutex);
	return (free(philos), 1);
}
