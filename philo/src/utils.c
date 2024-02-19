/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:34:03 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/19 13:33:53 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(char *message, char *el)
{
	if (el)
		write(STDERR_FILENO, el, ft_strlen(el));
	write(STDERR_FILENO, message, ft_strlen(message));
	return (EXIT_FAILURE);
}

int	change_state(t_timeval *tv, t_philo *philo, t_state state)
{
	philo->state = state;
	if (gettimeofday(tv, NULL))
		return (error(FUNCTION, "gettimeofday"));
	if (philo->state == HAS_FORK)
		printf("%d %u has taken a fork\n", tv->tv_usec, philo->nb);
	else if (philo->state == EATING)
		printf("%d %u is eating\n", tv->tv_usec, philo->nb);
	else if (philo->state == SLEEPING)
		printf("%d %u is sleeping\n", tv->tv_usec, philo->nb);
	else if (philo->state == THINKING)
		printf("%d %u is thinking\n", tv->tv_usec, philo->nb);
	else if (philo->state == DYING)
		printf("%d %u died\n", tv->tv_usec, philo->nb);
	return (EXIT_SUCCESS);
}
