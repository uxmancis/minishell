/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_2_redir_4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 13:17:33 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 14:39:43 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	set_red_index_type(t_box **box)
{
	int	i;
	int	index_of_arr;

	i = 0;
	index_of_arr = 0;
	put_parsing_box_numof_redir_2();
	while (i < (int)ft_strlen((*box)->input_substr))
	{
		if ((*box)->input_substr[i] == '<' && (*box)->dict_quotes[i] == 0)
		{
			if (set_red_less_than(box, &i, index_of_arr) == 0)
				index_of_arr++;
			else
				return (-1);
		}
		else if ((*box)->input_substr[i] == '>' && (*box)->dict_quotes[i] == 0)
		{
			if (set_red_greater_than(box, &i, index_of_arr) == 0)
				index_of_arr++;
			else
				return (-1);
		}
		i++;
	}
	return (0);
}

/*  set_red_greater_than
 *       Returns:
 *           0: Success - Redirection was assigned
 *           -1: Redirection was finally NOT assigned (inside quotes)
 */
int	set_red_greater_than(t_box **box, int *i, int index_of_arr)
{
	if ((*box)->input_substr[(*i)] != '>'
		&& (*box)->dict_quotes[(*i)] == 0)
		return (EXIT_FAILURE);
	else if ((*box)->input_substr[(*i)] == '>'
		&& (*box)->dict_quotes[(*i)] == 0)
	{
		if ((*box)->input_substr[(*i) + 1] == '>'
				&& (*box)->dict_quotes[(*i) + 1] == 0)
			set_red_greater_than_2(box, i, index_of_arr);
		else if ((*box)->input_substr[(*i) + 1] == '<'
			&& (*box)->dict_quotes[(*i) + 1] == 0)
		{
			ft_puterror("syntax error near unexpected token `newline'\n");
			return (-1);
		}
		else
			set_red_greater_than_3(box, i, index_of_arr);
	}
	put_parsing_box_numof_redir_3(box, index_of_arr);
	return (0);
}
