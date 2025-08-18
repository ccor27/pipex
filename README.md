## PipexMedic
The test 2, 5 and 6 from pipexMedic are test that are designed to recieve a no-standart
pipex project, because it expected when there are not path/enviroment search manually or just
add "/usr/bin/" manually to each command and execute it, but it only with the secon command
because the first one should exit silently 



## possible solution for test #2 of pipexMedic
´´´
static pid_t	ft_second_child(t_data *data, int pipe_fd[], int outfile_fd)
{
	pid_t	p2;

	p2 = fork();
	if (p2 < 0)
		ft_perror_exit(data, NULL, "fork (2)", 1);
	if (p2 == 0)
	{
		close(pipe_fd[1]);
		if (dup2(pipe_fd[0], STDIN_FILENO) < 0 || dup2(outfile_fd,
				STDOUT_FILENO) < 0)
			ft_perror_exit(data, NULL, "dup (2)", 1);
		close(outfile_fd);
		close(pipe_fd[0]);
		if (data->cmd_paths[1] == NULL)
		{
			if (execve(ft_strjoin("/usr/bin/", data->commands[1]),
					data->commands[1], data->envp) == -1)
				ft_handle_execve_error(data, NULL, data->commands[1][0], errno);
		}
		else if (execve(data->cmd_paths[1], data->commands[1], data->envp) ==
			-1)
			ft_handle_execve_error(data, NULL, data->commands[1][0], errno);
	}
	return (p2);
}

static pid_t	ft_first_child(t_data *data, int pipe_fd[], int infile_fd)
{
	pid_t	p1;

	p1 = fork();
	if (p1 < 0)
		ft_perror_exit(data, NULL, "fork (1)", 1);
	if (p1 == 0)
	{
		close(pipe_fd[0]);
		if (dup2(infile_fd, STDIN_FILENO) < 0 || dup2(pipe_fd[1],
				STDOUT_FILENO) < 0)
			ft_perror_exit(data, NULL, "dup (1)", 1);
		close(infile_fd);
		close(pipe_fd[1]);
		if (data->cmd_paths[0] == NULL)
			ft_perror_exit(data, NULL, NULL, 0);
		else if (execve(data->cmd_paths[0], data->commands[0], data->envp) ==
			-1)
			ft_handle_execve_error(data, NULL, data->commands[0][0], errno);
	}
	return (p1);
}
´´´
