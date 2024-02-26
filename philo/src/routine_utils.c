/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:38:46 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/26 14:55:20 by abasdere         ###   ########.fr       */
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

long long	ft_ogettime(t_philo *philo, long long *time)
{
	t_timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (sim_error(philo, FUNCTION, "gettimeofday"), *time = 0, *time);
	return (*time = tv.tv_sec * 1000 + tv.tv_usec / 1000, *time);
}

int	print_state(t_philo *philo)
{
	long long	time;

	if (!ft_ogettime(philo, &time))
		return (1);
	pthread_mutex_lock(philo->mutex_write);
	printf("[%lld] %u %s\n", time, philo->nb, find_message(philo->state));
	pthread_mutex_unlock(philo->mutex_write);
	return (0);
}

int	sim_error(t_philo *philo, char *message, char *el)
{
	pthread_mutex_lock(philo->mutex_finished);
	*(philo->finished) = philo->rules.total_nb;
	pthread_mutex_unlock(philo->mutex_finished);
	return (error(message, el));
}
