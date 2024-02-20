/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:43:53 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/20 13:05:09 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(t_philo *philo, t_args args)
{
	t_timeval	tv;

	(void)args;
	(void)philo;
	if (gettimeofday(&tv, NULL))
		return (error(FUNCTION, "gettimeofday"), NULL);
	// printf("%ld: %u is waiting\n", tv.tv_usec, philo->nb);
	while (1)
	{
	// 	if (change_state(&tv, philo, EATING))
	// 		return (1);
	// 	usleep(args.eat * 1000);
	// 	if (change_state(&tv, philo, SLEEPING))
	// 		return (1);
	// 	usleep(args.sleep * 1000);
	// 	if (change_state(&tv, philo, THINKING))
	// 		return (1);
	}
	return (NULL);
}
