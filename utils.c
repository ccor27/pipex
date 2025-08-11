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
void	ft_exit_and_free(t_data *data, char **paths, char *message)
{
	int i;
	int j;

	free(data->filenames[0]);
	free(data->filenames[1]);
	free(data->filenames);
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
	if(message)
		ft_printf("%s",message);
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

