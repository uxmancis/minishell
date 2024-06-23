/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_3_hrdc_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:28:28 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/19 15:10:54 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*Contains following functions: 
1. void ft_heredocs(t_box **box)
2. int ft_get_numof_heredocs(t_box **box)
3. void ft_check_delimiter(t_box **box)
4. void get_arr_heredoc(int **arr_ind_heredoc, t_box **box)
5. void get_end_arr(int **arr_end, t_box **box, int *arr_ind_heredoc)
*/

/* ft_heredocs
*       Checks whether if 100% heredocs have end delimiter.
*       
*       If heredocs is found with no end delimiter, then error message is printed
+       and minishell program finishes its execution.
*/
int	ft_heredocs(t_box **box, t_red_type red_type)
{
	(*box)->nb_of_heredocs = ft_get_numof_red_type(box, red_type);
	if (DEBUG_MODE != 0)
	{
		printf("     02_boxes_3_hrdc_1.c - "BLUE"ft_heredocs"RESET_COLOR);
		printf("| numof_heredocs = "BLUE"%d"RESET_COLOR".\n"
			, (*box)->nb_of_heredocs);
	}
	if (ft_check_first_word(box, red_type) == -1)
		return (-1);
	return (0);
}

/*get_arr_heredoc
*
*	x: dict_red_index_type[x]. Red number x. Starts from 0.
*/
void	get_arr_heredoc(int **arr_ind_heredoc, t_box **box)
{
	int	tmp_nb_of_heredocs;
	int	i;
	int	x;

	tmp_nb_of_heredocs = (*box)->nb_of_redir;
	i = 0;
	x = 0;
	while (tmp_nb_of_heredocs > 0)
	{
		if ((*box)->dict_red_index_type[x][1] == HEREDOC)
		{
			(*arr_ind_heredoc)[i] = (*box)->dict_red_index_type[x][0];
			i++;
		}
		x++;
		tmp_nb_of_heredocs--;
	}
}

/*get_end_arr: Informes arr_end variable: filled with 0 and 1.
*      1: YES end delimiter
*      0: NO end delimiter
*
* Variables:
*       int *arr_ind_heredoc: specific array which contains indexes of
*                             total heredocs found along input_substr.
*                             (based on nb_of_heredocs).
*       int red_nb_x: zenbagarren redirekziñua dan
*
*/
void	get_end_arr(int **arr_end, t_box **box, int *arr_ind_heredoc)
{
	int	tmp_nb_of_heredocs;
	int	i;

	tmp_nb_of_heredocs = (*box)->nb_of_heredocs;
	i = 0;
	while (tmp_nb_of_heredocs > 0)
	{
		(*arr_end)[i] = has_end_word(arr_ind_heredoc[i], box,
				get_ind(arr_ind_heredoc[i], box));
		tmp_nb_of_heredocs--;
		i++;
		if (DEBUG_MODE != 0)
		{
			printf(BLUE"arr_ind_heredoc[%d] = ", i);
			printf("%d\n"RESET_COLOR, arr_ind_heredoc[i]);
		}
	}
}
