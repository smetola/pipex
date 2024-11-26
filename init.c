/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanmetol <sanmetol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:15:42 by sanmetol          #+#    #+#             */
/*   Updated: 2024/11/26 22:27:32 by sanmetol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	create_pipes(t_pipex *pipex)
{
	int	i;

	pipex->pipes = malloc(sizeof(int *) * (pipex->cmd_count - 1));
	if (!pipex->pipes)
		return (1);
	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		pipex->pipes[i] = malloc(sizeof(int) * 2);
		if (!pipex->pipes[i] || pipe(pipex->pipes[i]) == -1)
		{
			perror("Error creating pipes");
			return (1);
		}
		i++;
	}
	return (0);
}

static void	init_heredoc(t_pipex *pipex, char **av)
{
	int		fd[2];
	char	*line;
	size_t	lim_len;

	if (pipe(fd) == -1)
		handle_error('p', "Error creating pipe for here_doc", EXIT_FAILURE);
	lim_len = ft_strlen(av[2]);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (ft_strncmp(line, av[2], lim_len) == 0 && line[lim_len] == '\n')
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	close(fd[1]);
	pipex->infile = fd[0];
}

static char	*find_cmd_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	if (!*envp)
		handle_error('f', "Error: PATH doesn't found\n", EXIT_FAILURE);
	return (*envp + 5);
}

void	init_pipex(t_pipex *pipex, int ac, char **av, char **envp)
{
	char	*paths;

	pipex->here_doc = (ft_strncmp(av[1], "here_doc", 8) == 0);
	pipex->cmd_count = ac - 3 - pipex->here_doc;
	if (pipex->here_doc)
		init_heredoc(pipex, av);
	else
		pipex->infile = open(av[1], O_RDONLY);
	if (pipex->infile < 0)
		handle_error('p', "Error opening infile", -1);
	if (pipex->here_doc)
		pipex->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		pipex->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile < 0)
	{
		close(pipex->infile);
		handle_error('p', "Error opening outfile", EXIT_FAILURE);
	}
	paths = find_cmd_path(envp);
	pipex->cmd_paths = ft_split(paths, ':');
}
