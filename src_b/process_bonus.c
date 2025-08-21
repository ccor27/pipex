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
		ft_handle_execve_error(data, NULL, data->commands[index][0], ENOENT);
	else
	{
		if (execve(data->cmd_paths[index], data->commands[index], data->envp) ==
			-1)
			ft_handle_execve_error(data, NULL, data->commands[index][0], errno);
	}
}

void	ft_dup_child(t_data *data, int index, int **pipes)
{
	if (index == 0) // first command
	{
		if (dup2(data->infile, STDIN_FILENO) < 0 || dup2(pipes[index][1],
				STDOUT_FILENO) < 0)
			ft_perror_exit(data, NULL, "dup", 1);
	}
	else if (index == data->num_commands - 1) // final command
	{
		if (dup2(pipes[index - 1][0], STDIN_FILENO) < 0 || dup2(data->outfile,
				STDOUT_FILENO) < 0)
			ft_perror_exit(data, NULL, "dup", 1);
	}
	else // middle commands
	{
		if (dup2(pipes[index - 1][0], STDIN_FILENO) < 0 || dup2(pipes[index][1],
				STDOUT_FILENO) < 0)
			ft_perror_exit(data, NULL, "dup", 1);
	}
	ft_close_all_pipes(pipes, data->num_commands - 1);
	close(data->infile);
	close(data->outfile);
	ft_exe_child(data, index);
}

void	ft_allocate_pipes_and_pids(t_data *data, int ***pipes, int **pids)
{
	int	i;

	i = 0;
	*pids = malloc(sizeof(int) * data->num_commands);
	if (!*pids)
		ft_perror_exit(data, NULL, "malloc pids", 1);
	*pipes = malloc(sizeof(int *) * (data->num_commands - 1));
	if (!*pipes)
		ft_perror_exit(data, NULL, "malloc pipes", 1);
	while (i < (data->num_commands - 1))
	{
		(*pipes)[i] = malloc(sizeof(int) * 2);
		if (!(*pipes)[i])
			ft_perror_exit(data, NULL, "malloc pipe[i]", 1);
		if (pipe((*pipes)[i]) < 0)
			ft_perror_exit(data, NULL, "pipe", 1);
		i++;
	}
}

int	ft_process(t_data *data)
{
	int	**pipes;
	int	*pids;
	int status;


	data->infile = open(data->filenames[0], O_RDONLY);
	if (data->infile < 0)
	{
		write(2, "pipex: ", 7);
		perror(data->filenames[0]);
		data->infile = open("/dev/null", O_RDONLY);
	}
	data->outfile = open(data->filenames[1], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (data->outfile < 0)
	{
		close(data->infile);
		ft_perror_exit(data, NULL, data->filenames[1], 126);
	}
	ft_allocate_pipes_and_pids(data, &pipes, &pids);
	status = ft_process_aux(data, pids, pipes);
	close(data->infile);
	close(data->outfile);
	return ((status >> 8) & 0xFF);
}

int	ft_process_aux(t_data *data, int *pids, int **pipes)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->num_commands)
	{
		pids[i] = fork();
		if (pids[i] < 0)
			ft_perror_exit(data, NULL, "fork", 1);
		else if (pids[i] == 0)
			ft_dup_child(data, i, pipes);
		i++;
	}
	ft_close_all_pipes(pipes, data->num_commands - 1);
	ft_wait_child(pids, &status, data->num_commands);
	free(pids);
	return status;
}
