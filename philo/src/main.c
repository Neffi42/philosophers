/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:55:12 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/28 12:59:18 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philo(t_philo *philo, t_vars *vars, t_rules *rules)
{
	philo->id = 0;
	philo->nb_meals = 0;
	philo->last_meal = 0;
	philo->state = THINKING;
	philo->rules = rules;
	philo->vars = vars;
	philo->thread = 0;
}

static int	init_philos(t_philo *philos, t_vars *vars, t_rules *rules)
{
	int	i;

	i = -1;
	while (++i < rules->total_nb)
	{
		init_philo(&(philos[i]), vars, rules);
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

static int	init_vars(t_vars *vars)
{
	t_timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (1);
	vars->s_time = tv.tv_sec * 1000000 + tv.tv_usec;
	if (init_var(&(vars->start), 0))
		return (1);
	if (pthread_mutex_init(&(vars->write), NULL))
		return (pthread_mutex_destroy(&(vars->start.mutex)), 1);
	return (0);
}

static int	monitor(t_philo *philos, t_rules *rules, t_vars *vars)
{
	int	i;

	while (get_var(&vars->start))
	{
		i = -1;
		while (++i < rules->total_nb)
			if (!get_var(&(philos[i].finished)))
				break ;
		if (i == rules->total_nb)
		{
			set_var(&vars->start, 0);
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
	t_vars		vars;

	if (check_rules(ac, av, &rules))
		return (1);
	philos = ft_calloc(rules.total_nb, sizeof(t_philo));
	if (!philos)
		return (error(FUNCTION, "malloc"));
	if (init_vars(&vars))
		return (free(philos), 1);
	if (init_philos(philos, &vars, &rules))
		return (1);
	set_var(&(vars.start), 1);
	return (monitor(philos, &rules, &vars));
}
