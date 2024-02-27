/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:55:12 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/27 15:31:33 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philo(t_philo *philo, t_shared *shared, t_rules *rules)
{
	philo->id = 0;
	philo->nb_meals = 0;
	philo->last_meal = 0;
	philo->state = THINKING;
	philo->rules = rules;
	philo->shared = shared;
	philo->thread = 0;
}

static int	init_philos(t_philo *philos, t_shared *shared, t_rules *rules)
{
	int	i;

	i = -1;
	while (++i < rules->total_nb)
		philos[i].id = 0;
	i = -1;
	while (++i < rules->total_nb)
	{
		init_philo(&(philos[i]), shared, rules);
		if (init_var(&(philos[i].fork), 0))
			return (destroy(philos, i));
		if (init_var(&(philos[i].finished), 0))
			return (pthread_mutex_destroy(&(philos[i].fork.mutex)),
				destroy(philos, i));
		if (pthread_create(&(philos[i].thread), NULL, routine, &philos[i]))
			return (error(FUNCTION, "pthread_create"), destroy(philos, i));
		philos[i].id = i + 1;
	}
	i = -1;
	while (++i < rules->total_nb)
		philos[i].fork2 = &(philos[(i + 1) % rules->total_nb].fork);
	return (0);
}

static int	init_shared(t_shared *shared)
{
	t_timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (1);
	shared->start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	if (init_var(&(shared->start), 0))
		return (1);
	if (pthread_mutex_init(&(shared->write), NULL))
		return (pthread_mutex_destroy(&(shared->start.mutex)), 1);
	return (0);
}

static int	monitor(t_philo *philos, t_rules *rules, t_shared *shared)
{
	int	i;

	while (get_var(&(shared->start)))
	{
		i = -1;
		while (++i < rules->total_nb)
			if (!get_var(&(philos[i].finished)))
				break ;
		if (i == rules->total_nb)
		{
			set_var(&(shared->start), 0);
			break ;
		}
		usleep(1);
	}
	return (destroy(philos, rules->total_nb), 0);
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
	if (init_philos(philos, &shared, &rules))
		return (1);
	set_var(&(shared.start), 1);
	return (monitor(philos, &rules, &shared));
}
