/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio < crosorio@student.42madrid.com>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-08 09:12:39 by crosorio          #+#    #+#             */
/*   Updated: 2025-08-08 09:12:39 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, int **argv)
{
	if(argc < 5)
		exit(EXIT_FAILURE);
	char *joined;
	/**
	 * TODO:
	 * 		-validate that arguments are not blank or empty
	 * 		-validate file or directory exist and has the permissions
	 * 			-using access()
	 * 		- validate a command exist and it's valid
	 * 			-get the path enviroment variable
	 * 			-iterate through each directory in the PATH and construct a
	 * 				full path to the command (e.g, /bin/ls)
	 * 			-For each constructed path, use access(full_path, X_OK)
	 * 				to check if the command exists and is executable
	 * 		- handle errors
	 */
	//get the arguments from position 2 to argv-2 into array
}
