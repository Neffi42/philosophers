/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:34:03 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/20 13:05:08 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(char *message, char *el)
{
	if (el)
		write(STDERR_FILENO, el, ft_strlen(el));
	write(STDERR_FILENO, message, ft_strlen(message));
	return (1);
}

// int	change_state(t_timeval *tv, t_philo *philo, t_state state)
// {
// 	philo->state = state;
// 	if (gettimeofday(tv, NULL))
// 		return (error(FUNCTION, "gettimeofday"));
// 	if (philo->state == HAS_FORK)
// 		printf("%ld %u has taken a fork\n", tv->tv_usec, philo->nb);
// 	else if (philo->state == EATING)
// 		printf("%ld %u is eating\n", tv->tv_usec, philo->nb);
// 	else if (philo->state == SLEEPING)
// 		printf("%ld %u is sleeping\n", tv->tv_usec, philo->nb);
// 	else if (philo->state == THINKING)
// 		printf("%ld %u is thinking\n", tv->tv_usec, philo->nb);
// 	else if (philo->state == DYING)
// 		printf("%ld %u died\n", tv->tv_usec, philo->nb);
// 	return (0);
// }
