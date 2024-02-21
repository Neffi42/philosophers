/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:34:03 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/21 14:25:26 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Prints an error message along with the provided element.
 *
 * This function is used to display an error message along with the element
 * that caused the error. It takes a message string and an element string as
 * parameters and prints them to the standard error stream.
 *
 * @param message The error message to be displayed.
 * @param el The element that caused the error.
 * @return The return value of the function is not specified.
 */
int	error(char *message, char *el)
{
	if (el)
		write(STDERR_FILENO, el, ft_strlen(el));
	write(STDERR_FILENO, message, ft_strlen(message));
	return (1);
}

/**
 * @brief Destroys the mutexes used in the program.
 *
 * This function is responsible for destroying the mutexes used in the program.
 * It takes a pointer to the data structure as a parameter.
 *
 * @param data A pointer to the data structure.
 */
static void	destroy_mutexes(t_data *data)
{
	size_t	i;

	i = -1;
	while (++i < data->args.nb)
		if (data->philos[i].nb != 0)
			pthread_mutex_destroy(&data->philos[i].fork);
}

/**
 * @brief Destroys the threads used in the program.
 *
 * This function is responsible for destroying the threads used in the program.
 * It takes a pointer to a `t_data` structure as a parameter.
 * The function does not return a value.
 */
static void	destroy_threads(t_data *data)
{
	size_t	i;

	i = -1;
	while (++i < data->args.nb)
		if (data->philos[i].thread)
			pthread_detach(data->philos[i].thread);
}

/**
 * @brief Destroys the data structure and frees allocated memory.
 *
 * @param data The pointer to the data structure to be destroyed.
 * @return int Returns 0 on success, -1 on failure.
 */
int	destroy(t_data *data)
{
	destroy_mutexes(data);
	destroy_threads(data);
	if (data->philos)
		free(data->philos);
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
