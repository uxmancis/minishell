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

//Pretends to be the single functions used for all redirections to check content (first word)
//after redirección.

//First, we'll copy the heredoc functions.
//Then, we'll try using them calling them both from heredoc, but also from other redir types.
//If successful, we'll delete previous specific functions for heredoc


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
*                     Len of array = number of redirecciones found of specified type (red_type).
*/
void	get_specif_index_red(int **arr_ind_red_type, t_box **box, t_red_type red_type)
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
	//para comprobaciones:
	tmp_nb_of_red_type = get_nb_of_red_type(box, red_type);
	i = 0;
	while (tmp_nb_of_red_type > 0)
	{
		//printf(MAGENTA"arr_ind_red_type[%d] = %d\n"RESET_COLOR, i, (*arr_ind_red_type)[i]);
		tmp_nb_of_red_type--;
		i++;
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
void	is_word_red(int **arr_word_yes_no, t_box **box, int *arr_ind_red_type, t_red_type red_type)
{
	int	tmp_nb_of_red_type;
	int	i;

	tmp_nb_of_red_type = get_nb_of_red_type(box, red_type);
	i = 0;
	while (tmp_nb_of_red_type > 0)
	{
		(*arr_word_yes_no)[i] = has_end_word(arr_ind_red_type[i], box, get_ind(arr_ind_red_type[i], box));
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

/*ft_check_first_word
*   Checks whether of 100% redirecciones in substr do have
*   a word after them. 
*
*       HEREDOC || INFILE: If redirección with no delimiter is found, 
*   error message is printed and program finishes its execution.
*
*       get_word_mgmt: gets first words to work as
*               HEREDOC: end delimiter word
*               INFILE: infile filename
*               OUTFILE (strong or append): outfile filename
*
*   Variables:
*       int *specif_arr_ind_red_type: specific array which
*		stores specific indexes of
*                              specified e_red_type.
*                              E.g. if HEREDOCS are going to 
+							   be analysed, array will store indexes
*								of HEREDOCS. If another type
*                                   of redirección is asked for (e_red_type), the
*                                   corresponding indexes will be stored.
*   
*       int *arr_word_yes_no: array which len is number of
*		redirecciones of X type.
*                     In each position stores 1 or 0, depending
*                     on if redirección has a word after it or not.
*
*   Returns:
*       -1: Error
*       0: Success
*
*/
int	ft_check_first_word(t_box **box, t_red_type red_type)
{
	int	*specif_arr_ind_red_type;
	int	*arr_word_yes_no;
	int	tmp_to_debug_nb_of_red_type;
	int	tmp_to_debug_i;
	int	nb_of_red_type;

	nb_of_red_type = get_nb_of_red_type(box, red_type);
	specif_arr_ind_red_type = malloc(sizeof(int) * nb_of_red_type);
	if (!specif_arr_ind_red_type)
		ft_puterror ("malloc error\n");
	get_specif_index_red(&specif_arr_ind_red_type, box, red_type);
	arr_word_yes_no = malloc(sizeof(int) * nb_of_red_type);
	is_word_red(&arr_word_yes_no, box, specif_arr_ind_red_type, red_type);
	tmp_to_debug_nb_of_red_type = nb_of_red_type;
	tmp_to_debug_i = 0;
	while (tmp_to_debug_nb_of_red_type > 0)
	{
		printf("           is WORD after red_type? YES-NO[%d] = "BLUE"%d\n"RESET_COLOR, tmp_to_debug_i, arr_word_yes_no[tmp_to_debug_i]);
		tmp_to_debug_nb_of_red_type--;
		tmp_to_debug_i++;
	}
	if (!are_all_delimiters(arr_word_yes_no, box, red_type))
	{
		if (put_error_red_type(red_type) == -1)
			return (-1);
	}
	get_word_mgmt(specif_arr_ind_red_type, box, red_type);
	free(arr_word_yes_no);
	free(specif_arr_ind_red_type);
	return (0);
}
