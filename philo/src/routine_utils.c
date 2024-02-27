/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:38:46 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/27 16:00:38 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*find_message(t_state state)
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

long long	get_time(t_philo *philo, long long *time)
{
	t_timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (error(FUNCTION, "gettimeofday"), 1);
	*time = tv.tv_sec * 1000 + tv.tv_usec / 1000 - philo->shared->start_time;
	return (0);
}

int	print_state(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&(philo->shared->write));
	if (get_var(&(philo->shared->start)) == 0)
		return (pthread_mutex_unlock(&(philo->shared->write)), 1);
	if (get_time(philo, &time))
		return (1);
	printf("%lld %u %s\n", time, philo->id, find_message(philo->state));
	pthread_mutex_unlock(&(philo->shared->write));
	return (0);
}
