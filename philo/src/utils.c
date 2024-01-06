/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 19:11:26 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/06 19:21:34 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(char *message)
{
	size_t	i;

	if (!message)
		return (EXIT_FAILURE);
	while (message[i])
		i++;
	write(STDERR_FILENO, message, i);
	return (EXIT_FAILURE);
}
