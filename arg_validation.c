/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio < crosorio@student.42madrid.com>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-08 09:22:31 by crosorio          #+#    #+#             */
/*   Updated: 2025-08-08 09:22:31 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Function to validate if a string is empty or blank
 */
int	ft_is_string_empty_or_blank(char *s)
{
	if (!s)
		return (1);
	while (*s)
	{
		if (!((*s >= 9 && *s <= 13) || *s == 32))
			return (0);
		s++;
	}
	return (1);
}

/**
 * Functionn to validate if the arguments are
 * empty or blanks strings
 */
int are_arguments_valid(char **arguments)
{
	int i;

	i = 1;
	while (arguments[i])
	{
		if(ft_is_string_empty_or_blank(arguments[i]))
			return(0);
		i++;
	}
	return(1);
}
