/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:34:03 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/07 16:15:21 by abasdere         ###   ########.fr       */
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
