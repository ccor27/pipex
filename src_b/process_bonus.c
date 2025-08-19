/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio <crosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 08:53:53 by crosorio          #+#    #+#             */
/*   Updated: 2025/08/19 21:29:25 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_exe_child(t_data *data, int index)
{
	if (data->cmd_paths[index] == NULL)
		ft_handle_execve_error(data, NULL, data->commands[0][0], ENOENT);
	else
	{
		if (execve(data->cmd_paths[index], data->commands[0], data->envp) == -1)
			ft_handle_execve_error(data, NULL, data->commands[index][0], errno);
	}
}

void	ft_dup_child(t_data *data, int index, int **pipes)
{
	if (index == 0) // first command
	{
		close(pipes[index][0]);
		if (dup2(data->infile, STDIN_FILENO < 0) || dup2(pipes[index][1],
				STDOUT_FILENO) < 0)
			ft_perror_exit(data, NULL, "dup", 1);
		close(data->infile);
		close(pipes[index][1]);
	}
	else if (index == data->num_commands - 1) // final command
	{
		close(pipes[index - 1][1]);
		if (dup2(pipes[index - 1][0], STDIN_FILENO) < 0 || dup2(data->outfile,
				STDOUT_FILENO) < 0)
			ft_perror_exit(data, NULL, "dup", 1);
		close(pipes[index - 1][0]);
	}
	else // middle commands
	{
		close(pipes[index - 1][1]);
		close(pipes[index][0]);
		if (dup2(pipes[index - 1][0], STDIN_FILENO) < 0 || dup2(pipes[index][1],
				STDOUT_FILENO) < 0)
			ft_perror_exit(data, NULL, "dup", 1);
		close(pipes[index - 1][0]);
		close(pipes[index][1]);
	}
	ft_exe_child(data, index);
}

int	ft_process(t_data *data)
{
	int	**pipes;
}
//TODO: finisht this that is to allocate and 
//initialize the pipe
void	ft_allocate_pipes(t_data *data, int ***pipes)
{
	int	i;

	i = 0;
	*pipes = malloc(sizeof(int *) * (data->num_commands - 1));
	if (!pipes)
		ft_perror_exit(data, NULL, "malloc pipes", 1);
	while (i < (data->num_commands - 1))
	{
		pipes[i][0] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			ft_perror_exit(data, NULL, "malloc pipe[i]", 1);
		if (pipe(pipes[i]) < 0)
			ft_perror_exit(data, NULL, "pipe", 1);
	}
}

/**
 * for (int i = 0; i < data->num_commands; i++)
{
	if (i < data->num_commands - 1)
		pipe(pipe_fd[i]);
			// Create pipe for this stage (unless it's the last command)
	pid = fork();
	if (pid == 0)
	{
		// First command: read from infile
		if (i == 0)
		{
			dup2(infile_fd, STDIN_FILENO);
			dup2(pipe_fd[i][1], STDOUT_FILENO);
		}
		// Last command: write to outfile
		else if (i == data->num_commands - 1)
		{
			dup2(pipe_fd[i - 1][0], STDIN_FILENO);
			dup2(outfile_fd, STDOUT_FILENO);
		}
		// Middle commands: read from previous pipe, write to current pipe
		else
		{
			dup2(pipe_fd[i - 1][0], STDIN_FILENO);
			dup2(pipe_fd[i][1], STDOUT_FILENO);
		}
		// Close all pipe FDs in child
		close_all_pipes(pipe_fd);
		execve(data->cmd_paths[i], data->commands[i], data->envp);
		ft_handle_execve_error(...); // Handle execve error
	}
	// In parent: close FDs that won't be used anymore
	if (i > 0)
	{
		close(pipe_fd[i - 1][0]);
		close(pipe_fd[i - 1][1]);
	}
}
 */