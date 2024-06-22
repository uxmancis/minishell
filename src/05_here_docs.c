/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_here_docs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:28:26 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 01:02:56 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_readline(t_box **box, char *line)
{
	if (!line)
		return (-1);

	if (ft_strcmp(line, (*box)->words_hrdc[0]) == 0)
	{
		(*box)->words_hrdc++;
		free(line);
		return (-1);
	}
	return (0);
}

int	handle_heredoc(t_box **box)
{
	int		heredoc_fd;
	char	*line;

	heredoc_fd = open("/tmp/heredoc.tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (heredoc_fd == -1 || (*box)->words_hrdc == NULL)
		return (-1);
	while (1)
	{
		line = readline("heredoc >");
		if (ft_readline(box, line) == -1)
			break ;
		write(heredoc_fd, line, ft_strlen(line));
		write(heredoc_fd, "\n", 1);
		free(line);
		line = NULL;
		(*box)->nb_of_heredocs--;
	}
	close(heredoc_fd);
	(*box)->fd_in = open("/tmp/heredoc.tmp", O_RDONLY);
	(*box)->close_in++;
	return (0);
}
