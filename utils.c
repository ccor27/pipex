/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio < crosorio@student.42madrid.com>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-09 12:50:34 by crosorio          #+#    #+#             */
/*   Updated: 2025-08-09 12:50:34 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Function to free memory and exit the program
 */
void	ft_exit_and_free(t_data *data, char **paths)
{
	int i;
	int j;

	free(data->filenames[0]);
	free(data->filenames[1]);
	i = 0;
	while(data->commands[i])
	{
		j=0;
		while (data->commands[i][j])
		{
			free(data->commands[i][j]);
			j++;
		}
		free(data->commands[i]);
		i++;
	}
	free(data->commands);
	if(paths)
		ft_free_paths(paths);
	exit(EXIT_FAILURE);
}

/**
 *Function to free the memory of the matrix that
 *contains the paths
 */
void	ft_free_paths(char **paths)
{
	int i = 0;
	while(paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

/**
 * You only need to validate the command name,
 * which is the first argument of each command (data->commands[i][0]).
 *  The rest of the arguments (-l, -a, etc.) are handled by the command itself
 * and don't affect whether the command can be found in the PATH.
 */
