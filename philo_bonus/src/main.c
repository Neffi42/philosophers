/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:55:12 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/29 10:40:10 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	run(t_philo *philos, t_rules *rules, t_sems *sems)
{
	sems->bool_run = 1;
	sem_post(sems->run);
	while (1)
	{
		(usleep(1000), sem_wait(sems->run), sem_wait(sems->meals));
		if (sems->bool_run == 0)
		{
			(sem_post(sems->meals), sem_post(sems->run));
			break ;
		}
		if (rules->total_meals && sems->nb_meals >= rules->total_nb)
		{
			sems->bool_run = 0;
			(sem_post(sems->meals), sem_post(sems->run));
			break ;
		}
		(sem_post(sems->meals), sem_post(sems->run));
	}
	return (destroy(philos, rules->total_nb), 0);
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
	if (init_philos(philos, &sems, &rules))
		return (1);
	return (run(philos, &rules, &sems));
}
