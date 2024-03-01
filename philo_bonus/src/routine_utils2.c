/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:35:35 by abasdere          #+#    #+#             */
/*   Updated: 2024/03/01 12:55:53 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_usleep(t_philo *philo, int time_to_sleep)
{
	time_t	end_time;
	time_t	cu_time;

	if (get_time(philo, &cu_time))
		return (1);
	end_time = cu_time + time_to_sleep;
	while (cu_time < end_time)
	{
		usleep(10);
		if (get_time(philo, &cu_time))
			return (1);
		if (check_for_dead(philo))
			return (1);
	}
	if (check_for_dead(philo))
		return (1);
	return (0);
}

void	stop(t_philo *philo)
{
	sem_wait(philo->sems->run);
	philo->sems->bool_run = 0;
	sem_post(philo->sems->run);
}

void	*one_philo(t_philo *philo)
{
	t_timeval	tv;
	time_t		time;

	if (gettimeofday(&tv, NULL))
		return (error(FCT, "gettimeofday"), stop(philo), NULL);
	time = tv.tv_sec * 1000000 + tv.tv_usec - philo->rules->s_time;
	printf("%ld %u has taken a fork\n", time / 1000, philo->id);
	usleep(philo->rules->time_die);
	return (NULL);
}
