/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_7_dollar_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:55:05 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 00:27:37 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	cpy_arr_with_len_2(int *arr_src, int **arr_dst, int len)
{
	int	i;

	i = 0;
	while (len > 0)
	{
		(*arr_dst)[i] = arr_src[i];
		printf("dict para ander[%d] = %d\n", i, (*arr_dst)[i]);
		i++;
		len--;
	}
}


//void replace_env_1


/*  replace_env
*
*   When still more info after replacing content, cpy rest.
*/
void	replace_env_last(t_w_d **w_d, int keep_len_new_word, char *keep_old_word, int *keep_old_dict)
{
	//(*w_d)->ind_old_word++;
	while ((*w_d)->y < keep_len_new_word)
	{
		//printf(BLUE"y = %d, ind_old_word = %d\n"RESET_COLOR, (*w_d)->y, (*w_d)->ind_old_word);
		(*w_d)->w2update[(*w_d)->y] = keep_old_word[(*w_d)->ind_old_word];
		(*w_d)->dict_q_to_update[(*w_d)->y] = keep_old_dict[(*w_d)->ind_old_word];
		(*w_d)->y++;
		(*w_d)->ind_old_word++;
	}
}

void	replace_env_step_2(t_w_d **w_d, int len_str_to_find, char *tmp_val)
{
	(*w_d)->ind_old_word++;
	while (len_str_to_find > 0)
	{
		(*w_d)->ind_old_word++;
		len_str_to_find--;
	}
	while ((*w_d)->len_val > 0)
	{
		(*w_d)->w2update[(*w_d)->y] = tmp_val[(*w_d)->ind_val];
		(*w_d)->dict_q_to_update[(*w_d)->y] = 0;
		(*w_d)->ind_val++;
		(*w_d)->y++;
		(*w_d)->len_val--;
	}
}

void	replace_env_step_1(t_w_d **w_d, char *keep_old_word, int *keep_old_dict_quotes_word)
{
	while ((*w_d)->ind_new_word < (*w_d)->ind_dollar)
	{
		(*w_d)->w2update[(*w_d)->y] = keep_old_word[(*w_d)->ind_old_word];
		(*w_d)->dict_q_to_update[(*w_d)->y] = keep_old_dict_quotes_word[(*w_d)->ind_old_word];
		(*w_d)->ind_new_word++;
		(*w_d)->ind_old_word++;
		(*w_d)->y++;
		(*w_d)->new_len--;
	}
}

void	set_w_d(t_w_d **w_d, int y, char **w2up, int **tmp_dict_quotes_word)
{
	(*w_d)->ind_dollar = y;
	(*w_d)->y = 0;
	(*w_d)->w2update = *w2up;
	(*w_d)->dict_q_to_update = *tmp_dict_quotes_word;
	(*w_d)->ind_old_word = 0;
	(*w_d)->ind_new_word = 0;
	(*w_d)->ind_val = 0;
}

/*  cpy_everything
* //1. si antes del dólar hay cositas, copiarlas
* //2. una vez llegamos a la posición del dólar
* //3. Si todavía hay más info después de val
*
*/
void cpy_everything (t_w_d **w_d, char *keep_old_word, int *keep_old_dict_quotes_word)
{
	if ((*w_d)->ind_new_word < (*w_d)->ind_dollar)
		replace_env_step_1(w_d, keep_old_word, keep_old_dict_quotes_word);
	if ((*w_d)->ind_new_word == (*w_d)->ind_dollar)
		replace_env_step_2(w_d, (*w_d)->len_str_to_find, (*w_d)->tmp_val);
	if ((*w_d)->y < (*w_d)->keep_len_new_word)
		replace_env_last(w_d, (*w_d)->keep_len_new_word, keep_old_word, keep_old_dict_quotes_word);
	(void)(*w_d)->keep_len_new_word;
}

/*
*   w2up: word_to_be_updated
*/
void	replace_env(char **w2up, t_x_y_word x_y, char *tmp_val, int **tmp_dict_quotes_word)
{
	char	*keep_old_word;
	int		len_old_word;
	int		*keep_old_dict_quotes_word;
	t_w_d	*w_d;

    printf("replace_env\n");
	w_d = malloc(sizeof(t_w_d) * 1);
	w_d->w2update = NULL;
	w_d->dict_q_to_update = NULL;
	w_d->tmp_val = NULL;
    len_old_word = ft_strlen(*w2up);
	printf("len_old_word = %d, word = %s\n", len_old_word, *w2up);
    keep_old_word = malloc(sizeof(char) * (ft_strlen(*w2up) + 1));
    keep_old_word[ft_strlen(*w2up)] = '\0';
    get_old_word(*w2up, &keep_old_word);
    keep_old_dict_quotes_word = malloc(sizeof(int) * len_old_word);
    cpy_arr_with_len_2(*tmp_dict_quotes_word, &keep_old_dict_quotes_word, len_old_word);
    w_d->len_str_to_find = ft_strlen(get_word_2(keep_old_word, x_y));
    ft_free_word_and_dict(w2up, tmp_dict_quotes_word);
    w_d->new_len = ft_strlen(keep_old_word) - 1 - w_d->len_str_to_find + ft_strlen(tmp_val);
    *w2up = malloc(sizeof(char)*(w_d->new_len + 1));
    (*w2up)[w_d->new_len] = '\0';
    *tmp_dict_quotes_word = malloc(sizeof(int) * w_d->new_len);
	set_w_d(&w_d, x_y.index_y, w2up, tmp_dict_quotes_word);
	w_d->tmp_val = tmp_val;
	w_d->len_val = ft_strlen(tmp_val);
	w_d->keep_len_new_word = w_d->new_len;
	printf("new_len = %d\n, OLD word = %s\n\n", w_d->new_len, keep_old_word);
	cpy_everything(&w_d, keep_old_word, keep_old_dict_quotes_word);
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
