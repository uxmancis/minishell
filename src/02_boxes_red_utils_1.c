/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_red_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:25:19 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/19 15:11:28 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
*	Pretends to be the single functions used for all redirections
*	to check content (first word) after redirección.
*
*	First, we'll copy the heredoc functions.
*	Then, we'll try using them calling them both from heredoc,
*	but also from other redir types.
*
*	If successful, we'll delete previous specific functions for heredoc.
*/

/*get_nb_of_red_type
*
*   Gets e_red_type as input: HEREDOC / INFILE / OUTFILE_APPEND / OUTFILE_STRONG
*
*   Returns: counter, total number of redirecciones found of specified
*            type in dict_red_index_type (box). 
*/
int	get_nb_of_red_type(t_box **box, t_red_type red_type)
{
	int	tmp_nb_of_redir;
	int	i;
	int	counter;

	tmp_nb_of_redir = (*box)->nb_of_redir;
	i = 0;
	counter = 0;
	while (tmp_nb_of_redir > 0)
	{
		if ((*box)->dictred_i_t[i][1] == (int)red_type)
			counter++;
		tmp_nb_of_redir--;
		i++;
	}
	return (counter);
}

/* get_specif_index_red
*
*   Informs specif_arr_ind_red_type.
*
*   specif_arr_ind_red_type: stores indexes of red_type specified.
*                     Len of array = number of redirecciones found
*					  of specified type (red_type).
*/
void	get_specif_index_red(int **arr_ind_red_type,
		t_box **box, t_red_type red_type)
{
	int	tmp_nb_of_red_type;
	int	i;
	int	x;

	tmp_nb_of_red_type = get_nb_of_red_type(box, red_type);
	i = 0;
	x = 0;
	while (tmp_nb_of_red_type > 0)
	{
		if ((*box)->dictred_i_t[x][1] == (int)red_type)
		{
			(*arr_ind_red_type)[i] = (*box)->dictred_i_t[x][0];
			i++;
			tmp_nb_of_red_type--;
		}
		x++;
	}
}

/*get_word_red: Informes arr_word_yes_no variable: filled with 0 and 1.
*      1: YES word was found
*      0: NO word was found
*
* Variables:
*       int *arr_ind_red_type: specific array which contains indexes of
*                             total redireccioness found along input_substr of
*                             specified red type (e_red_type):
*/
void	is_word_red(int **arr_word_yes_no, t_box **box,
		int *arr_ind_red_type, t_red_type red_type)
{
	int	tmp_nb_of_red_type;
	int	i;

	tmp_nb_of_red_type = get_nb_of_red_type(box, red_type);
	i = 0;
	while (tmp_nb_of_red_type > 0)
	{
		(*arr_word_yes_no)[i] = has_end_word(arr_ind_red_type[i],
				box, get_ind(arr_ind_red_type[i], box));
		tmp_nb_of_red_type--;
		i++;
	}
}

/*are_all_delimiters
*
*   e_red_type specifies type of redirección to be analysed:
*       HEREDOC / INFILE / OUTFILE_APPEND / OUTFILE_STRONG  
*
*   Returns:
*       1 - YES all red_type specified have word next to them
*       0 - NO, redirección was found with no word next to it
*/
int	are_all_delimiters(int *arr_word_yes_no, t_box **box, t_red_type red_type)
{
	int	tmp_nb_of_red_type;
	int	i;

	tmp_nb_of_red_type = get_nb_of_red_type(box, red_type);
	i = 0;
	while (tmp_nb_of_red_type > 0)
	{
		if (arr_word_yes_no[i] == 0)
			return (0);
		tmp_nb_of_red_type--;
		i++;
	}
	return (1);
}

int	put_error_red_type(enum e_red_type red_type)
{
	if (red_type == HEREDOC)
	{
		ft_puterror("syntax error near unexpected token `<<'\n");
		return (-1);
	}
	else if (red_type == INFILE)
	{
		ft_puterror("syntax error near unexpected token `<'\n");
		return (-1);
	}
	else if (red_type == OUTFILE_APPEND)
	{
		ft_puterror("syntax error near unexpected token `>>'\n");
		return (-1);
	}
	else if (red_type == OUTFILE_STRONG)
	{
		ft_puterror("syntax error near unexpected token `>'\n");
		return (-1);
	}
	return (0);
}
