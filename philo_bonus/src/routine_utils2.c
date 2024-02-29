/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:35:35 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/29 14:59:37 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	stop(t_philo *philo)
{
	sem_wait(philo->sems->run);
	philo->sems->bool_run = 0;
	sem_post(philo->sems->run);
	usleep(1000);
}

void	*one_philo(t_philo *philo)
{
	t_timeval	tv;
	time_t		time;

	stop(philo);
	if (gettimeofday(&tv, NULL))
		(error(FCT, "gettimeofday"), destroy(philo->origin, 1));
	time = tv.tv_sec * 1000000 + tv.tv_usec - philo->rules->s_time;
	printf("%ld %u has taken a fork\n", time / 1000, philo->id);
	usleep(philo->rules->time_die);
	if (gettimeofday(&tv, NULL))
		(error(FCT, "gettimeofday"), destroy(philo->origin, 1));
	time = tv.tv_sec * 1000000 + tv.tv_usec - philo->rules->s_time;
	printf("%ld %u died\n", time / 1000, philo->id);

	destroy(philo->origin, 1);
}
