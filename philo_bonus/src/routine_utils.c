/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:38:46 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/29 10:14:16 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

time_t	get_time(t_philo *philo, time_t *time)
{
	t_timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		sem_wait(philo->sems->run);
		philo->sems->run = 0;
		sem_post(philo->sems->run);
		return (error(FCT, "gettimeofday"));
	}
	*time = tv.tv_sec * 1000000 + tv.tv_usec - philo->rules->s_time;
	return (0);
}

static char	*find_message(t_state state)
{
	if (state == HAS_FORK)
		return ("has taken a fork");
	else if (state == EATING)
		return ("is eating");
	else if (state == SLEEPING)
		return ("is sleeping");
	else if (state == THINKING)
		return ("is thinking");
	else
		return ("died");
}

int	print_state(t_philo *philo, t_state state)
{
	time_t	time;

	sem_wait(philo->sems->write);
	if (state != DEAD)
	{
		sem_wait(philo->sems->run);
		if (philo->sems->bool_run == 0)
			return (sem_post(philo->sems->write),
				sem_post(philo->sems->run), 1);
		sem_post(philo->sems->run);
	}
	if (get_time(philo, &time))
		return (1);
	printf("%ld %u %s\n", time / 1000, philo->id, find_message(state));
	sem_post(philo->sems->write);
	return (0);
}

int	is_philo_dead(t_philo *philo)
{
	time_t	cu_time;

	sem_wait(philo->sems->run);
	if (philo->sems->bool_run == 0)
		return (sem_post(philo->sems->run), 1);
	sem_post(philo->sems->run);
	if (get_time(philo, &cu_time))
		return (1);
	if (cu_time - philo->last_meal > philo->rules->time_die)
	{
		sem_wait(philo->sems->run);
		philo->sems->run = 0;
		sem_post(philo->sems->run);
		return (print_state(philo, DEAD), 1);
	}
	return (0);
}

int	ft_usleep(t_philo *philo, int time_to_sleep)
{
	time_t	end_time;
	time_t	cu_time;

	if (get_time(philo, &cu_time))
		return (1);
	end_time = cu_time + time_to_sleep;
	while (cu_time < end_time)
	{
		usleep(250);
		if (get_time(philo, &cu_time))
			return (1);
		if (is_philo_dead(philo))
			return (1);
	}
	return (0);
}
