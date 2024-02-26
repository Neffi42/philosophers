/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:55:12 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/26 11:06:36 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_arg(int *data, const char *av)
{
	char	*tmp;

	*data = ft_atoi(av);
	if (!*data)
		return (error(ARGUMENT, (char *)av));
	tmp = ft_itoa(*data);
	if (!tmp)
		return (error(FUNCTION, "ft_uitoa"));
	if (ft_strncmp(av, tmp, ft_strlen((char *)av) + 1))
		return (free(tmp), error(ARGUMENT, (char *)av));
	if (*data <= 0)
		return (free(tmp), error(ARGUMENT, (char *)av));
	return (free(tmp), 0);
}

static int	check_rules(int ac, const char **av, t_rules *rules)
{
	if (ac < 5 || ac > 6)
		return (error(USAGE, NULL));
	if (check_arg(&rules->total_nb, av[1])
		|| check_arg(&rules->time_die, av[2])
		|| check_arg(&rules->time_eat, av[3])
		|| check_arg(&rules->time_sleep, av[4]))
		return (1);
	if (ac == 5)
		rules->total_eat = 0;
	else if (check_arg(&rules->total_eat, av[5]))
		return (1);
	if (rules->total_nb > 300)
		return (error(NBR_PHILO, (char *)av[1]));
	return (0);
}

static int	monitor(t_philo *philos, t_rules rules, t_shared *shared)
{
	while (1)
	{
		pthread_mutex_lock(&(shared->mutex_finished));
		if (shared->finished < 0 || shared->finished >= rules.total_nb)
		{
			pthread_mutex_lock(&(shared->mutex_start));
			shared->start = 0;
			pthread_mutex_unlock(&(shared->mutex_start));
			pthread_mutex_unlock(&(shared->mutex_finished));
			break ;
		}
		pthread_mutex_unlock(&(shared->mutex_finished));
		usleep(1000);
	}
	return (destroy(philos, rules.total_nb), 0);
}

int	main(int ac, const char **av)
{
	t_philo		*philos;
	t_rules		rules;
	t_shared	shared;

	if (check_rules(ac, av, &rules))
		return (1);
	philos = ft_calloc(rules.total_nb, sizeof(t_philo));
	if (!philos)
		return (error(FUNCTION, "malloc"));
	if (init_shared(&shared))
		return (free(philos), 1);
	pthread_mutex_lock(&(shared.mutex_start));
	if (init_philos(philos, &shared, rules))
		return (1);
	pthread_mutex_unlock(&(shared.mutex_start));
	return (destroy(philos, rules.total_nb), 0);
	return (monitor(philos, rules, &shared));
}
