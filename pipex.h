/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanmetol <sanmetol@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:22:28 by sanmetol          #+#    #+#             */
/*   Updated: 2024/11/26 22:27:14 by sanmetol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/wait.h>
# include "gnl/get_next_line.h"

# define ERROR_MS "Please enter: \n\t\" "\
		"\n\t\"./pipex infile cmd1 cmd2 ... outfile\" or "\
		"\n\t\"./pipex here_doc LIMITER cmd1 cmd2 outfile"

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		here_doc;
	char	**cmd_paths;
	int		cmd_count;
	int		**pipes;
}	t_pipex;

char	**ft_split(const char *s, char c);
void	ft_putstr_fd(const char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	close_pipes(t_pipex *pipex);
void	cleanup(t_pipex *pipex);
void	free_cmd_args(char **cmd_args);
void	handle_error(char errType, const char *msg, int exit_code);
int		create_pipes(t_pipex *pipex);
void	init_pipex(t_pipex *pipex, int ac, char **av, char **envp);
int		fork_and_exec(t_pipex *pipex, char **argv, char **envp);

#endif