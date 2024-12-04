/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanmetol <sanmetol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:47:53 by sanmetol          #+#    #+#             */
/*   Updated: 2024/11/26 22:27:54 by sanmetol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		i;

	if (argc < 5 || (argc < 6 && !ft_strncmp(argv[1], "here_doc", 8)))
		handle_error('f', ERROR_MS, EXIT_FAILURE);
	init_pipex(&pipex, argc, argv, envp);
	create_pipes(&pipex);
	fork_and_exec(&pipex, argv, envp);
	close_pipes(&pipex);
	i = 0;
	while (i < pipex.cmd_count)
	{
		wait(NULL);
		i++;
	}
	cleanup(&pipex);
	return (0);
}

//DEBUGGER: fprintf(stderr, "Mensaje de depuración\n");
// ./pipex infile "grep a1" "wc -w" outfile
// ./pipex infile "grep a1 -v" "sort" "uniq" "wc -w" outfile
// ./pipex here\_doc END "grep a" "wc -l" outfile
	// grep a << END | wc -l >> outfile
// valgrind --leak-check=full