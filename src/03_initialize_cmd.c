/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_initialize_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:02:43 by dbonilla          #+#    #+#             */
/*   Updated: 2024/06/23 20:43:36 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	setup_box(t_box **box, t_prompt *data, int box_id)
{
	(*box)->nb_cmd = box_id;
	(*box)->nb_pipes = data->nb_of_pipes;
	if (handle_redirects(box) == -1)
		return (-1);
	if (close_files(*box) == -1)
		return (-1);
	return (0);
}

int	init_data_cmd(t_box **box, t_prompt *data, int box_id)
{
	(*box)->pids = malloc(sizeof *(*box)->pids * (*box)->nb_cmd);
	if (!(*box)->pids)
		return (-1);
	create_child_process(*box, data, box_id - 1);
	return (0);
}

int	init_cmd(t_box **box, t_prompt *data, int box_id)
{
	if (setup_box(box, data, box_id) == -1)
		return (-1);
	if (init_data_cmd(box, data, box_id) == -1)
		return (-1);
	return (0);
}

int	handle_redirects(t_box **box)
{
	int		tmp_nb_of_red_type;
	int		index_red;

	index_red = 0;
	tmp_nb_of_red_type = (*box)->nb_of_redir;
	while (tmp_nb_of_red_type > 0)
	{
		if (process_redirect(box, index_red) == -1)
			return (-1);
		index_red++;
		tmp_nb_of_red_type--;
	}
	restore_original_pointers(box);
	return (0);
}
