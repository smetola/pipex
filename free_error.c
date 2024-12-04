/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanmetol <sanmetol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:39:06 by sanmetol          #+#    #+#             */
/*   Updated: 2024/11/26 22:26:50 by sanmetol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		close(pipex->pipes[i][0]);
		close(pipex->pipes[i][1]);
		i++;
	}
}

void	cleanup(t_pipex *pipex)
{
	int	i;

	close_pipes(pipex);
	close(pipex->infile);
	close(pipex->outfile);
	if (pipex->here_doc)
		unlink("/tmp/heredoc_pipex");
	i = 0;
	while (pipex->cmd_paths && pipex->cmd_paths[i])
		free(pipex->cmd_paths[i++]);
	free(pipex->cmd_paths);
	i = 0;
	while (i < pipex->cmd_count - 1)
		free(pipex->pipes[i++]);
	free(pipex->pipes);
}

void	free_cmd_args(char **cmd_args)
{
	int	i;

	i = 0;
	while (cmd_args[i])
		free(cmd_args[i++]);
	free(cmd_args);
}

void	handle_error(char errType, const char *msg, int exit_code)
{
	//fprintf(stderr, "Mensaje de depuración, error: %d\n msg: %s\n", exit_code, msg);
	if (errType == 'p')
		perror(msg);
	else
		ft_putstr_fd(msg, STDERR_FILENO);
	if (exit_code != -1)
		exit(exit_code);
}
