/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:39:33 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/20 13:05:00 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_mutexes(t_data *data)
{
	size_t	i;

	i = -1;
	while (++i < data->args.nb)
		pthread_mutex_destroy(&data->philos[i].fork);
}

static void	destroy_threads(t_data *data)
{
	size_t	i;

	i = -1;
	while (++i < data->args.nb)
		pthread_detach(data->philos[i].thread);
}

void destroy(t_data *data)
{
	destroy_mutexes(data);
	destroy_threads(data);
	if (data->philos)
		free(data->philos);
}
