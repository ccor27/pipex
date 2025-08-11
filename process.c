/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio < crosorio@student.42madrid.com>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-11 12:31:36 by crosorio          #+#    #+#             */
/*   Updated: 2025-08-11 12:31:36 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_execute_child(t_data *data, int pipe_fd[], char child, int fd)
{
	if (child == '1')
	{
		close(pipe_fd[0]);
		if (dup2(fd, STDIN_FILENO) < 0 || dup2(pipe_fd[1], STDOUT_FILENO) < 0)
			ft_exit_and_free(data, NULL,"Error, making the dup2 of child (1)\n");
		close(fd);
		close(pipe_fd[1]);
		if (execve(data->commands[0][0], data->commands[0], data->envp) == -1)
			ft_exit_and_free(data, NULL,"Error, making the execve (1)\n");
	}
	else
	{
		close(pipe_fd[1]);
		if (dup2(pipe_fd[0], STDIN_FILENO) < 0 || dup2(fd, STDOUT_FILENO) < 0)
			ft_exit_and_free(data, NULL,"Error, making the dup2 of child (2) \n");
		close(fd);
		close(pipe_fd[0]);
		if (execve(data->commands[1][0], data->commands[1], data->envp) == -1)
			ft_exit_and_free(data, NULL,"Error, making the execve (2) \n");
	}
}
void	ft_process(t_data *data)
{
	int		pipe_fd[2];
	int		infile_fd;
	int		outfile_fd;
	pid_t	p1;
	pid_t	p2;

	infile_fd = open(data->filenames[0], O_RDONLY);
	outfile_fd = open(data->filenames[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (infile_fd < 0 || outfile_fd < 0)
		ft_exit_and_free(data, NULL,"Error, in file cannot open\n");
	pipe(pipe_fd);
	p1 = fork();
	if (p1 < 0)
		ft_exit_and_free(data, NULL,"Error, creation of child\n");
	if(p1 == 0)
		ft_execute_child(data, pipe_fd, '1', infile_fd);
	p2 = fork();
	if (p2 < 0)
		ft_exit_and_free(data, NULL,"Error, creation of child\n");
	if(p2 == 0)
		ft_execute_child(data, pipe_fd, '2', outfile_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(-1,NULL,0);
	waitpid(-1,NULL,0);
}
