/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:34:03 by abasdere          #+#    #+#             */
/*   Updated: 2024/02/21 15:06:25 by abasdere         ###   ########.fr       */
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
 * @brief Destroys the mutexes associated with the philosophers.
 *
 * This function is responsible for destroying
 * the mutexes that were created for the philosophers.
 * It takes a pointer to the `t_philo` structure as a parameter.
 *
 * @param philos A pointer to the `t_philo` structure.
 */
static void	destroy_mutexes(t_philo *philos)
{
	size_t	i;

	i = -1;
	while (++i < philos->args->nb)
		if (philos[i].nb != 0)
			pthread_mutex_destroy(&(philos[i].fork));
}

/**
 * @brief Destroys the threads associated with the philosophers.
 *
 * @param philos The array of philosopher structures.
 */
static void	destroy_threads(t_philo *philos)
{
	size_t	i;

	i = -1;
	while (++i < philos->args->nb)
		if (philos[i].thread)
			pthread_join(philos[i].thread, NULL);
}

/**
 * @brief Destroys the philosopher objects.
 *
 * This function is responsible for freeing
 * the memory allocated for the philosopher objects.
 *
 * @param philos The array of philosopher objects.
 * @return int Returns 0 on success, -1 on failure.
 */
int	destroy(t_philo *philos)
{
	if (!philos)
		return (1);
	destroy_threads(philos);
	destroy_mutexes(philos);
	free(philos);
	return (1);
}
