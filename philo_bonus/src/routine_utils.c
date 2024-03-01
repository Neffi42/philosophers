/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:38:46 by abasdere          #+#    #+#             */
/*   Updated: 2024/03/01 10:59:03 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	get_time(t_philo *philo, time_t *time)
{
	t_timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (stop(philo), error(FCT, "gettimeofday"), 1);
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
	if (check_for_dead(philo) || is_philo_dead(philo))
		return (sem_post(philo->sems->write), 1);
	if (get_time(philo, &time))
		return (sem_post(philo->sems->write), 1);
	printf("%ld %u %s\n", time / 1000, philo->id, find_message(state));
	return (sem_post(philo->sems->write), 0);
}

int	check_for_dead(t_philo *philos)
{
	sem_wait(philos->sems->run);
	if (philos->sems->bool_run == 0)
		return (sem_post(philos->sems->run), 1);
	return (sem_post(philos->sems->run), 0);
}

int	is_philo_dead(t_philo *philo)
{
	time_t	cu_time;

	if (get_time(philo, &cu_time))
		return (1);
	if (cu_time - philo->last_meal > philo->rules->time_die)
	{
		if (check_for_dead(philo))
			return (1);
		stop(philo);
		printf("%ld %u died\n", cu_time / 1000, philo->id);
		return (1);
	}
	return (0);
}
