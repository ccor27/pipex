/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio < crosorio@student.42madrid.com>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-21 14:50:15 by crosorio          #+#    #+#             */
/*   Updated: 2025-08-21 14:50:15 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_wait_child(int *pids, int *status, int n)
{
	int	i;
	int tmp_status;

	i = 0;
	while (i < n)
	{
		if (pids[i] > 0)
		{
			if(waitpid(pids[i], &tmp_status, 0) == pids[n -1])
				*status= tmp_status;
		}
		i++;
	}
}

void	ft_close_all_pipes(int **pipes, int n)
{
	int	i;
	int	j;

	i = 0;
	while (i < n)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

/**
 * Function to free memory of the struct
 */
void	ft_free_memory(t_data *data, char **paths)
{
	int	i;
	int	j;

	if (data->filenames)
	{
		free(data->filenames[0]);
		free(data->filenames[1]);
		free(data->filenames);
	}
	i = 0;
	if (data->commands)
	{
		while (data->commands[i])
		{
			j = 0;
			while (data->commands[i][j])
				free(data->commands[i][j++]);
			free(data->commands[i++]);
		}
		free(data->commands);
	}
	if (paths)
		ft_free_paths(paths);
	if (data->cmd_paths)
		ft_free_cmd_paths(data);
}

void	ft_free_cmd_paths(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmd_paths[i])
		free(data->cmd_paths[i++]);
	free(data->cmd_paths);
}

/**
 *Function to free the memory of the matrix that
 *contains the paths
 */
void	ft_free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}
