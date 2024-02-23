/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:55:12 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/23 13:01:23 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_arg(unsigned int *data, const char *av)
{
	char	*tmp;

	*data = ft_atoui(av);
	if (!*data)
		return (error(ARGUMENT, (char *)av));
	tmp = ft_uitoa(*data);
	if (!tmp)
		return (error(FUNCTION, "ft_uitoa"));
	if (ft_strncmp(av, tmp, ft_strlen((char *)av) + 1))
		return (free(tmp), error(ARGUMENT, (char *)av));
	return (free(tmp), 0);
}

static int	check_args(int ac, const char **av, t_args *args)
{
	if (ac < 5 || ac > 6)
		return (error(USAGE, NULL));
	if (check_arg(&args->total_nb, av[1])
		|| check_arg(&args->time_die, av[2])
		|| check_arg(&args->time_eat, av[3])
		|| check_arg(&args->time_sleep, av[4]))
		return (1);
	if (ac == 5)
		args->total_eat = 0;
	else if (check_arg(&args->total_eat, av[5]))
		return (1);
	return (0);
}

static int	monitor(t_philo *philos, t_args args, t_shared *shared)
{
	while (1)
	{
		if (args.total_eat)
		{
			pthread_mutex_lock(&(shared->mutex_finished));
			if (shared->finished == args.total_nb)
			{
				(pthread_mutex_lock(&(shared->start)), shared->start = 0);
				pthread_mutex_unlock(&(shared->start));
			}
			pthread_mutex_unlock(&(shared->mutex_finished));
		}
		pthread_mutex_lock(&(shared->start));
		if (!shared->start)
			break ;
		pthread_mutex_unlock(&(shared->start));
		usleep(1000);
	}
	return (destroy(philos, args.total_nb), 0);
}

int	main(int ac, const char **av)
{
	t_philo		*philos;
	t_args		args;
	t_shared	shared;

	if (check_args(ac, av, &args))
		return (1);
	philos = ft_calloc(args.total_nb, sizeof(t_philo));
	if (!philos)
		return (error(FUNCTION, "malloc"));
	if (init_shared(&shared))
		return (free(philos), 1);
	pthread_mutex_lock(&(shared.mutex_start));
	if (init_philos(philos, &shared, args))
		return (1);
	pthread_mutex_unlock(&(shared.mutex_start));
	return (monitor(philos, args, &shared));
}
