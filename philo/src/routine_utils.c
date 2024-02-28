/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:38:46 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/28 14:01:55 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time(t_philo *philo, time_t *time)
{
	t_timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		set_var(&philo->vars->start, 0);
		return (error(FUNCTION, "gettimeofday"));
	}
	*time = tv.tv_sec * 1000000 + tv.tv_usec - philo->vars->s_time;
	return (0);
}

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

int	print_state(t_philo *philo)
{
	time_t	time;

	pthread_mutex_lock(&(philo->vars->write));
	if (DEAD != philo->state && get_var(&philo->vars->start) == 0)
		return (pthread_mutex_unlock(&(philo->vars->write)), 1);
	if (get_time(philo, &time))
		return (1);
	printf("%ld %u %s\n", time / 1000, philo->id, find_message(philo->state));
	pthread_mutex_unlock(&(philo->vars->write));
	return (0);
}

int	is_philo_dead(t_philo *philo)
{
	time_t	cu_time;

	if (get_var(&philo->vars->start) == 0)
		return (1);
	if (get_time(philo, &cu_time))
		return (1);
	if (cu_time - philo->last_meal > philo->rules->time_die)
	{
		(set_var(&philo->vars->start, 0), philo->state = DEAD);
		print_state(philo);
		return (1);
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
		usleep(10);
		if (get_time(philo, &cu_time))
			return (1);
		if (is_philo_dead(philo))
			return (1);
	}
	return (0);
}
