/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanmetol <sanmetol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:27:44 by sanmetol          #+#    #+#             */
/*   Updated: 2024/11/26 22:27:03 by sanmetol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		if (!tmp)
			return (NULL);
		command = ft_strjoin(tmp, cmd);
		if (!command)
			return (NULL);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		command = NULL;
		paths++;
	}
	return (NULL);
}

static int	exec_cmd(t_pipex *pipex, char *command, char **envp)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = ft_split(command, ' ');
	if (!cmd_args)
		handle_error('p', "Error splitting command", 1);
	cmd_path = get_cmd(pipex->cmd_paths, cmd_args[0]);
	if (!cmd_path)
	{
		free_cmd_args(cmd_args);
		handle_error('p', "Command not found", 127);
	}
	if (execve(cmd_path, cmd_args, envp) == -1)
	{
		free_cmd_args(cmd_args);
		handle_error('p', "Error executing command", 1);
	}
	return (0);
}

static void	dup_and_exec(t_pipex *pipex, char *cmd, int cmd_index, char **envp)
{
	if (cmd_index == 0)
		dup2(pipex->infile, STDIN_FILENO);
	else
		dup2(pipex->pipes[cmd_index - 1][0], STDIN_FILENO);
	if (cmd_index == pipex->cmd_count - 1)
		dup2(pipex->outfile, STDOUT_FILENO);
	else
		dup2(pipex->pipes[cmd_index][1], STDOUT_FILENO);
	close_pipes(pipex);
	exec_cmd(pipex, cmd, envp);
	handle_error('p', "Error executing cmd", 1);
}

int	fork_and_exec(t_pipex *pipex, char **argv, char **envp)
{
	int	i;
	int	pid;

	i = 0;
	while (i < pipex->cmd_count)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("Error creating fork");
			return (1);
		}
		if (pid == 0)
			dup_and_exec(pipex, argv[i + 2 + pipex->here_doc], i, envp);
		i++;
	}
	return (0);
}