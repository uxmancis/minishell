/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_2_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/05/19 15:10:51 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// useful to debug: to print enum name
char	*ft_enum_to_str(int enumerator)
{
	if (enumerator == NO_REDIRECTION)
		return ("NO_REDIRECTION");
	else if (enumerator == OUTFILE_APPEND)
		return (">>: OUTFILE_APPEND");
	else if (enumerator == OUTFILE_STRONG)
		return (">: OUTFILE_STRONG");
	else if (enumerator == INFILE)
		return ("<: INFILE");
	else if (enumerator == HEREDOC)
		return ("<<: HEREDOC");
	else
		return ("ERROR\n");
}

/*check_if_three_redirs
 *
 *	Returns:
 *		-1: Error: 3rd redirección was found
 *		0: Success: no 3rd redirección
 */
int	check_if_three_redirs(t_box **box, int i)
{
	if (((*box)->input_substr[i + 2] == '<'
			|| (*box)->input_substr[i + 2] == '>')
		&& (*box)->dict_quotes[i + 2] == 0)
	{
		ft_puterror("syntax error near unexpected token `newline'\n");
		return (-1);
	}
	return (0);
}

int	ft_fill_red_info(t_box **box)
{
	int	i;
	int	tmp_nb_of_red;

	i = 0;
	tmp_nb_of_red = (*box)->nb_of_redir;
	while (tmp_nb_of_red > 0)
	{
		(*box)->dict_red_index_type[i] = malloc(sizeof(int) * 2);
		tmp_nb_of_red--;
		i++;
	}
	if (set_red_index_type(box) == -1)
		return (-1);
	//printf("     02_boxes.c - ft_fill_red_info|" BLUE " dict_red_index_type" RESET_COLOR " generated✅\n");
    return (0);
}

/*ft_is_redir
 *
 *   Checks whether if there are any redirections along our
 *   input_substr to be analysed.
 *
 *   Returns:
 *       0: No redirections found along input_substr
 *       1: Yes, some redirections were found
 *
 *   Also, if YES (1) redirections were found, ft_fill_red_info function
 *   is called. In it,  information of found redirections is stored in
 *   total_red_type_index variable member (t_box) in the following way:
 *       [0]: Redirection type
 *       [1]: Redirection index in input_substr
 *
 *	ft_fill_red_info: total_red_type_index is set
 */
int	get_redirections(t_box **box)
{
	if (ft_get_numof_redir(box) == -1)
		return (-1);
	else
		(*box)->nb_of_redir = ft_get_numof_redir(box);
	if ((*box)->nb_of_redir == 0)
		return (0);
	(*box)->dict_red_index_type = malloc(sizeof(char *) * ((*box)->nb_of_redir));
	if (ft_fill_red_info(box) == -1)
		return (-1);
	return (1);
}
