/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crosorio <crosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 09:12:39 by crosorio          #+#    #+#             */
/*   Updated: 2025/08/08 21:36:07 by crosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, int **argv)
{
	if(argc < 5)
		exit(EXIT_FAILURE);
	if(!ft_are_arguments_valid(argv))
		exit(EXIT_FAILURE);
	
}
