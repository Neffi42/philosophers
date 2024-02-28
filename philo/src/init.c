/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:58:33 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/28 15:51:45 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philo(t_philo *philo, t_vars *vars, t_rules *rules, int i)
{
	philo->id = i + 1;
	philo->nb_meals = 0;
	philo->last_meal = 0;
	philo->rules = rules;
	philo->vars = vars;
	philo->thread = 0;
}

int	init_philos(t_philo *philos, t_vars *vars, t_rules *rules)
{
	int	i;

	i = -1;
	while (++i < rules->total_nb)
	{
		init_philo(&(philos[i]), vars, rules, i);
		if (init_var(&(philos[i].fork), 0))
			return (destroy(philos, i));
		if (pthread_create(&(philos[i].thread), NULL, routine, &philos[i]))
			return (error(FCT, "pthread_create"), destroy(philos, i));
	}
	i = -1;
	while (++i < rules->total_nb)
		philos[i].fork2 = &(philos[(i + 1) % rules->total_nb].fork);
	return (0);
}

int	init_vars(t_vars *vars)
{
	t_timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (1);
	vars->s_time = tv.tv_sec * 1000000 + tv.tv_usec;
	if (init_var(&vars->run, 0))
		return (1);
	if (pthread_mutex_init(&vars->write, NULL))
		return (pthread_mutex_destroy(&vars->run.mutex), 1);
	if (init_var(&vars->meals, 0))
		return (pthread_mutex_destroy(&vars->run.mutex),
			pthread_mutex_destroy(&vars->write), 1);
	return (0);
}
