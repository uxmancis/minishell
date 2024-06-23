/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_7_dollar_12.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 21:05:36 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 23:43:57 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*  is_in_env
 *
 *   Checks whether if WORD is found along variables in environment (list).
 *
 *   ft_get_env_local(xxx, str_to_find)
 *       E.g.: ft_get_env_local(data->vars, "USER")
 */
// int	is_in_env(char *old_word_before_free, t_x_y_word x_y, t_prompt **prompt)
// {
// 	char	*tmp;

// 	tmp = NULL;
// 	tmp = get_word_2(old_word_before_free, x_y);
// 	if (ft_getenv_local((*prompt)->vars, tmp))
// 	{
// 		if (tmp)
// 		{
// 			free(tmp);
// 			tmp = NULL;
// 		}
// 		return (1);
// 	}
// 	if (tmp)
// 	{
// 		free(tmp);
// 		tmp = NULL;
// 	}
// 	return (0);
// }
// void	get_old_word(char *str_src, char **str_dst)
// {
// 	int	len_src;
// 	int	i;

// 	len_src = ft_strlen(str_src);
// 	i = 0;
// 	while (len_src > 0)
// 	{
// 		(*str_dst)[i] = str_src[i];
// 		len_src--;
// 		i++;
// 	}
// }

/*get_each_word_updated
*
*   Infinite loop until no more dollars are found in word.
*
*   Word = the corresponding word in char **rest_info_potential_cmd (box).
*
*   We'll call this get_updated_words function for each of the words in
*   the variable.
*
*   What does get_updated_words do? Checks dollars:
*       $ --> replaces by $ (character), stays same
*       $$ --> replaces by pid
*       $ENV_VARIABE --> replaces by variable of environment
*
*	While(1)
*		1st, tmp_dict_quotes is updated (Function: generate_specif_dict_quotes)
*		2nd, find_dollars_and_replace
*		3rd, is there any other dollar? (Function: no_more_dollars)
*
*	w = word_to_be_updated (short because of norminette: Line too long)
*/
//void	get_each_word_updated(t_box **box, int nb_word_x, t_prompt **prompt)
void	get_each_word_up(char **w, int nb_word_x,
	t_box **box, t_prompt **prompt)
{
	int			len_word;
	int			*tmp_dict_quotes_word;
	t_x_y_word	x_y;

	if (DEBUG_MODE != 0)
		printf("               Before: ["MAGENTA"%s"RESET_COLOR"]\n", *w);
	x_y.index_x = nb_word_x;
	x_y.index_y = 0;
	tmp_dict_quotes_word = NULL;
	len_word = ft_strlen(*w);
	tmp_dict_quotes_word = generate_specif_dict_quotes(box, *w,
			nb_word_x, (*box)->flag_word_or_cmd);
	while (1)
	{
		len_word = ft_strlen(*w);
		find_dollar_replace(w, &x_y, &tmp_dict_quotes_word, prompt);
		if (no_more_dollars(*w, x_y, tmp_dict_quotes_word)
			|| x_y.index_y == len_word)
			break ;
		x_y.index_y++;
	}
	if (DEBUG_MODE != 0)
		printf("               After: ["YELLOW"%s"RESET_COLOR"]\n\n", *w);
	free (tmp_dict_quotes_word);
}
