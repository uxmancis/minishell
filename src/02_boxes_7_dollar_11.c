/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_7_dollar_11.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 21:05:36 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 21:42:55 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*  cpy_everything
* //1. si antes del dólar hay cositas, copiarlas
* //2. una vez llegamos a la posición del dólar
* //3. Si todavía hay más info después de val
*
*/
void	cpy_everything(t_w_d **w_d, char *keep_old_word,
	int *keep_old_dict_quotes_word)
{
	if ((*w_d)->ind_new_word < (*w_d)->ind_dollar)
		replace_env_step_1(w_d, keep_old_word, keep_old_dict_quotes_word);
	if ((*w_d)->ind_new_word == (*w_d)->ind_dollar)
		replace_env_step_2(w_d, (*w_d)->len_str_to_find, (*w_d)->tmp_val);
	if ((*w_d)->y < (*w_d)->keep_len_new_word)
		replace_env_last(w_d, (*w_d)->keep_len_new_word,
			keep_old_word, keep_old_dict_quotes_word);
	(void)(*w_d)->keep_len_new_word;
}

/*
*   w2up: word_to_be_updated
*	keep_old: keep_old_dict_quotes_word
*	k: keep_old_word
*/
void	replace_env(char **w2up, t_x_y_word x_y,
	char *tmp_val, int **tmp_dict_quotes_word)
{
	char	*k;
	int		len_old_word;
	int		*keep_old;
	t_w_d	*w_d;

	w_d = malloc(sizeof(t_w_d) * 1);
	ft_memset(w_d, 0, sizeof(t_w_d));
	len_old_word = ft_strlen(*w2up);
	k = malloc(sizeof(char) * (ft_strlen(*w2up) + 1));
	k[ft_strlen(*w2up)] = '\0';
	get_old_word(*w2up, &k);
	keep_old = malloc(sizeof(int) * len_old_word);
	cpy_arr_with_len_2(*tmp_dict_quotes_word, &keep_old, len_old_word);
	w_d->len_str_to_find = ft_strlen(get_word_2(k, x_y));
	ft_free_word_and_dict(w2up, tmp_dict_quotes_word);
	w_d->new_len = ft_strlen(k) - 1 - w_d->len_str_to_find + ft_strlen(tmp_val);
	*w2up = malloc(sizeof(char) * (w_d->new_len + 1));
	(*w2up)[w_d->new_len] = '\0';
	*tmp_dict_quotes_word = malloc(sizeof(int) * w_d->new_len);
	set_w_d(&w_d, x_y.index_y, w2up, tmp_dict_quotes_word);
	w_d->tmp_val = tmp_val;
	w_d->len_val = ft_strlen(tmp_val);
	w_d->keep_len_new_word = w_d->new_len;
	cpy_everything(&w_d, k, keep_old);
}

/*get_word_2
*
*   Returns: char *env_variable = the word we will aim to find in env.
*
*
*   Called from is_in_env
*/
char	*get_word_2(char *old_word_before_free, t_x_y_word x_y)
{
	char	*env_variable;
	int		len_word;
	int		x;

	(void)old_word_before_free;
	if (old_word_before_free)
		len_word = get_len_word(old_word_before_free, x_y);
	else
		len_word = get_len_word_3(old_word_before_free, x_y);
	env_variable = malloc(sizeof(char) * (len_word + 1));
	env_variable[len_word] = '\0';
	x_y.index_y++;
	x = 0;
	while (len_word > 0)
	{
		env_variable[x] = old_word_before_free[x_y.index_y];
		len_word--;
		x++;
		x_y.index_y++;
	}
	return (env_variable);
}

/*get_word_2
*
*   Returns: char *env_variable = the word we will aim to find in env.
*
*
*   Called from is_in_env
*/
char	*get_word_4(char *old_word_before_free, t_x_y_word x_y)
{
	char	*env_variable;
	int		len_word;
	int		x;

	if (old_word_before_free)
		len_word = get_len_word(old_word_before_free, x_y);
	else
		len_word = get_len_word_3(old_word_before_free, x_y);
	if (len_word == 0)
		return (NULL);
	env_variable = malloc(sizeof(char) * (len_word + 1));
	env_variable[len_word] = '\0';
	x_y.index_y++;
	x = 0;
	while (len_word > 0)
	{
		env_variable[x] = old_word_before_free[x_y.index_y];
		len_word--;
		x++;
		x_y.index_y++;
	}
	return (env_variable);
}

void	cpy_to_val(char *str_src, char **str_dst)
{
	int	len;
	int	i;

	len = ft_strlen(str_src);
	i = 0;
	while (len > 0)
	{
		(*str_dst)[i] = str_src[i];
		len--;
		i++;
	}
}
