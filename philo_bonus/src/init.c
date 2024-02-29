/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:58:33 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/29 14:55:06 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_philos(t_philo *philos, t_sems *sems, t_rules *rules)
{
	int	i;

	i = -1;
	while (++i < rules->total_nb)
	{
		philos[i].id = i + 1;
		philos[i].nb_meals = 0;
		philos[i].last_meal = 0;
		philos[i].thread = 0;
		philos[i].rules = rules;
		philos[i].sems = sems;
		philos[i].origin = philos;
		if (pthread_create(&(philos[i].thread), NULL, routine, &philos[i]))
			(error(FCT, "pthread_create"), destroy(philos, 1));
	}
}

int	init_sems(t_sems *sems, int total_nb)
{
	unlink_sem();
	sems->bool_run = 0;
	sems->nb_meals = 0;
	sems->run = sem_open("run", O_CREAT, 0644, 1);
	if (sems->run == SEM_FAILED)
		return (error(FCT, "sem_open"), 1);
	sems->meals = sem_open("meals", O_CREAT, 0644, 1);
	if (sems->meals == SEM_FAILED)
		return (destroy_sem(sems->run, "run"), error(FCT, "sem_open"), 1);
	sems->write = sem_open("write", O_CREAT, 0644, 1);
	if (sems->write == SEM_FAILED)
		return (destroy_sem(sems->run, "run"),
			destroy_sem(sems->meals, "meals"), error(FCT, "sem_open"), 1);
	sems->forks = sem_open("forks", O_CREAT, 0644, total_nb);
	if (sems->forks == SEM_FAILED)
		return (destroy_sem(sems->run, "run"),
			destroy_sem(sems->meals, "meals"),
			destroy_sem(sems->write, "write"), error(FCT, "sem_open"), 1);
	return (0);
}
