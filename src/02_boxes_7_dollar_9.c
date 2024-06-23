/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_7_dollar_9.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 14:32:18 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 15:39:55 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_isalnum_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isalnum(str[i]))
			return (-1);
		i++;
	}
	return (0);
}

/*
*   return (0) only used to exit function when next_is_space
*
*   tmp_dict_quotes_word hay que pasarlo como int **, ya que hay ciertas
*   funciones 
*   a las que se les llama desde find_dollars_and_replace que sí que modifican
*   los valores de la variable. E.g.: fill_with_nine, replace_pid_sec_dollar, 
*   finish_to_update_dict_quotes. Todos estos ejemplos particularmente se llaman 
*   desde mng_to_replace_sec_dollar. En el resto de funciones (foto actual)
*   la variable puede pasarse desreferenciada, ya que las funciones a las
*   que llamamos
*   únicamente serán usuarios de la variable, pero no la modificarán.
*
*   w: word_to_be_updated = shorteded because of norminette (line too long)
*/
int	find_dollar_replace(char **w, t_x_y_word *x_y, int **dict, t_prompt **p)
{
	char	*word;

	word = NULL;
	if (is_dollar(*w, *x_y, *dict))
	{
		if (next_is_space_or_end(*w, *x_y))
			return (0);
		else if (next_is_sec_dollar(*w, *x_y))
			mng_to_replace_sec_dollar(w, *x_y, dict);
		else if (next_is_question(*w, *x_y))
			x_y->index_y++;
		else if (is_in_env(*w, *x_y, p))
			mng_to_replace_env(w, *x_y, p, dict);
		else
		{
			word = get_word_4(*w, *x_y);
			if (word == NULL || ft_isalnum_str(word) == -1)
			{
				x_y->index_y++;
				if (word)
				{
					free (word);
					word = NULL;
				}
				return (0);
			}
			mng_to_replace_delete(w, *x_y);
			x_y->index_y--;
		}
	}
	if (word)
	{
		free (word);
		word = NULL;
	}
	return (0);
}

/*no_more_dollars
*  Returns:
*       1: Success, no more dollars were found allong word
*		  (taking quotes into account)
*       0: Still more dollars to be analysed and then replaced
*/
int	no_more_dollars(char *w, t_x_y_word x_y, int *dict)
{
	int	len_word;
	int	i;

	len_word = ft_strlen(w);
	i = 0;
	x_y.index_y = 0;
	while (len_word > 0)
	{
		if (is_dollar(w, x_y, dict))
			return (0);
		i++;
		x_y.index_y++;
		len_word--;
	}
	return (1);
}

/*generate_specif_dict_quotes
*
*	nb_word_x is fixed. We're in 1 particular word. nb_word_x won't change.
*
*	Additional explanatory comments:
*		 //cuando vamos a generar dict_quotes porque estamos queriendo
*		expandir C = Comandos. Variable en box: rest_info_potential_cmd
*
*	w = word_to_be_updated (short because of norminette: Line too long)
*/
int	*generate_specif_dict_quotes(t_box **box, char *w, int nb_word_x, char flag)
{
	int	*tmp_dict_quotes_word;
	int	start;

	tmp_dict_quotes_word = malloc(sizeof(int) * ft_strlen(w));
	if (flag == 'C')
		start = (*box)->index_beginning_words_rest[nb_word_x];
	else if (flag == 'W')
		start = 0;
	fill_tmp_dict_quotes(box, &tmp_dict_quotes_word, ft_strlen(w), start);
	return (tmp_dict_quotes_word);
}

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
