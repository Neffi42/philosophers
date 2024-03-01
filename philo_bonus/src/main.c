/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:55:12 by abasdere          #+#    #+#             */
/*   Updated: 2024/03/01 15:21:53 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	flood_stop(t_philo *philos, time_t cu_time, int dead)
{
	int	i;

	i = -1;
	stop(philos);
	printf("%ld %u died\n", cu_time / 1000, philos[dead].id);
	while (++i < 2 * philos->rules->total_nb)
	{
		sem_post(philos->sems->run);
		sem_post(philos->sems->meals);
		sem_post(philos->sems->write);
		sem_post(philos->sems->forks);
	}
	destroy(philos, 1, philos->rules->total_nb);
}

static void	monitor(t_philo *philos, t_rules *rules)
{
	int		i;
	time_t	cu_time;

	i = -1;
	if (check_for_dead(philos))
		destroy(philos, 1, rules->total_nb);
	while (++i < rules->total_nb)
	{
		if (get_time(philos, &cu_time))
			destroy(philos, 1, rules->total_nb);
		if (cu_time - philos[i].last_meal >= rules->time_die)
			break ;
	}
	if (i < rules->total_nb)
		flood_stop(philos, cu_time, i);
}

static void	run(t_philo *philos, t_rules *rules, t_sems *sems)
{
	sems->bool_run = 1;
	sem_post(sems->run);
	while (1)
	{
		usleep(1000);
		monitor(philos, rules);
		if (rules->total_meals)
		{
			sem_wait(sems->meals);
			monitor(philos, rules);
			if (sems->nb_meals >= rules->total_nb)
				(stop(philos), sem_post(sems->meals),
					destroy(philos, 0, rules->total_nb));
			sem_post(sems->meals);
		}
	}
}

int	main(int ac, const char **av)
{
	t_philo		*philos;
	t_rules		rules;
	t_sems		sems;
	t_timeval	tv;

	if (check_rules(ac, av, &rules))
		return (1);
	if (init_sems(&sems, rules.total_nb))
		return (1);
	if (gettimeofday(&tv, NULL))
		return (close_sem(&sems), unlink_sem(), 1);
	rules.s_time = tv.tv_sec * 1000000 + tv.tv_usec;
	philos = ft_calloc(rules.total_nb, sizeof(t_philo));
	if (!philos)
		return (1);
	sem_wait(sems.run);
	init_philos(philos, &sems, &rules);
	run(philos, &rules, &sems);
}
