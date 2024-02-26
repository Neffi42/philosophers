/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:43:53 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/26 11:25:53 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*find_message(t_state state)
{
	if (state == EATING)
		return ("has taken a fork");
	else if (state == SLEEPING)
		return ("is eating");
	else if (state == THINKING)
		return ("is sleeping");
	else if (state == HAS_FORK)
		return ("is thinking");
	else
		return ("died");
}

t_state	find_new_state(t_state state)
{
	if (state == EATING)
		return (SLEEPING);
	else if (state == SLEEPING)
		return (THINKING);
	else if (state == THINKING)
		return (HAS_FORK);
	else if (state == HAS_FORK)
		return (EATING);
	else
		return (DEAD);
}

static long long	ft_ogettime(t_philo *philo, long long *time)
{
	t_timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (sim_error(philo, FUNCTION, "gettimeofday"), *time = 0, *time);
	return (*time = tv.tv_sec * 1000 + tv.tv_usec / 1000, *time);
}

int	change_state(t_philo *philo, t_state state)
{
	long long	time;

	philo->state = state;
	if (!ft_ogettime(philo, &time))
		return (1);
	pthread_mutex_lock(philo->mutex_write);
	printf("[%lld] %u %s\n", time, philo->nb, find_message(state));
	pthread_mutex_unlock(philo->mutex_write);
	return (0);
}

void	*routine(void *arg)
{
	t_philo		*philo;
	long long	time;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->mutex_start);
	pthread_mutex_unlock(philo->mutex_start);
	if (philo->nb % 2 == 0)
		usleep(philo->rules.time_eat * 1000);
	if (!ft_ogettime(philo, &time))
		return (NULL);
	while (!simulation(philo, time))
		if (!ft_ogettime(philo, &time))
			return (NULL);
	return (NULL);
}
