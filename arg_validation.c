/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio <crosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 09:22:31 by crosorio          #+#    #+#             */
/*   Updated: 2025/08/08 21:36:45 by crosorio         ###   ########.fr       */
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
int ft_are_arguments_valid(char **arguments)
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

/**
 * To the matrix of the function of belong...
 * just make sure:

    matrix has been allocated with at least (arg_size - 3 + 1) elements.

    You handle potential memory allocation failures from ft_split() later.
 */

/**
 * Function to store the commands into an matrix
 */
void	ft_store_commands(int arg_size, char **arguments, char **matrix)
{
	int i;
	int j;

	i = 2;
	j = 0;
	while (i < arg_size - 1)
	{
		matrix[j]=ft_split(arguments[i],' ');
		i++;
		j++;
	}
	matrix[j] = NULL;
}
