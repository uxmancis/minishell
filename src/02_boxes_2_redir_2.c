/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_2_redir_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 13:48:41 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/18 21:53:12 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	plusplus_counter_i(int *counter, int *i)
{
	*counter = *counter + 1;
	*i = *i + 1;
}

void	plusplus_2(int *counter, int *i)
{
	*counter = *counter + 1;
	*i = *i + 2;
}

void	plusminus(int *len, int *i)
{
	*len = *len - 1;
	*i = *i + 1;
}

/*
*	Return:
*		-1: Error: 3rd redir found
*/
int	ft_get_numof_redir_part_2(t_box **box, int *i, int *counter)
{
	if ((((*box)->input_substr[*i + 1] == '<'
				|| (*box)->input_substr[*i + 1] == '>'))
		&& (*box)->dict_quotes[*i + 1] == 0)
	{
		if (check_if_three_redirs(box, *i) == -1)
			return (-1);
		else if ((*box)->dict_quotes[*i] == 0)
			plusplus_2(counter, i);
	}
	else if ((*box)->dict_quotes[*i] == 0)
		plusplus_counter_i(counter, i);
	return (0);
}

// int ft_check_if_redir redir(t_box *box, char *input)
/* ft_get_numof_redir
 *
 *   Returns:
 *       -1: Error (E.g.: 3rd redirección was found)
 *		0: Success
 *
 *	Explanatory comments:
 *		//1st redirección found
 *			if (i < keep_len && (box->input_substr[i] == '<' 
 *			|| box->input_substr[i] == '>' ))
 *		//2nd redirección found
 *			else if (box->dict_quotes[i] == 0)
 *
 */
int	ft_get_numof_redir(t_box **box)
{
	int	i;
	int	counter;
	int	len;
	int	keep_len;

	i = 0;
	counter = 0;
	len = (int)ft_strlen((*box)->input_substr);
	keep_len = len;
	while (i < keep_len)
	{
		if (i < keep_len && ((*box)->input_substr[i] == '<'
				|| (*box)->input_substr[i] == '>')
			&& (*box)->dict_quotes[i] == 0)
		{
			if (ft_get_numof_redir_part_2(box, &i, &counter) == -1)
				return (-1);
		}
		plusminus(&len, &i);
	}
	put_parsing_box_numof_redir(counter);
	return (counter);
}
