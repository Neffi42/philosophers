/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:43:53 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/21 15:09:48 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	change_state(t_philo *philo, t_state state)
{
	t_timeval	tv;

	philo->state = state;
	if (gettimeofday(&tv, NULL))
		return (error(FUNCTION, "gettimeofday"));
	if (philo->state == HAS_FORK)
		printf("%ld %u has taken a fork\n", tv.tv_sec, philo->nb);
	else if (philo->state == EATING)
		printf("%ld %u is eating\n", tv.tv_sec, philo->nb);
	else if (philo->state == SLEEPING)
		printf("%ld %u is sleeping\n", tv.tv_sec, philo->nb);
	else if (philo->state == THINKING)
		printf("%ld %u is thinking\n", tv.tv_sec, philo->nb);
	else if (philo->state == DYING)
		printf("%ld %u died\n", tv.tv_sec, philo->nb);
	return (0);
}

void	*routine(void *arg)
{
	t_timeval	tv;
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (gettimeofday(&tv, NULL))
		return (error(FUNCTION, "gettimeofday"), NULL);
	printf("time: %ld\t%u is waiting\n", tv.tv_sec, philo->nb);
	while (philo->args->start == 0)
		;
	change_state(philo, EATING);
	return (NULL);
}
