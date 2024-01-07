/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasdere <abasdere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:34:03 by abasdere          #+#    #+#             */
/*   Updated: 2024/01/07 15:34:12 by abasdere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(char *message)
{
	write(STDERR_FILENO, message, ft_strlen(message));
	return (EXIT_FAILURE);
}
