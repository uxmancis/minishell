/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_7_dollar_10.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 14:44:58 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 21:42:24 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*mng_to_replace_env
*
*   VAL = el valor por el que vamos a sustituir la palabra. The content of
*   assigned to X variable in env.
*
*   E.g.:
*       get_word_2 result = USER (word to look for in env)
*       char *tmp_val = uxmancis (VAL = result = assigned content
*		to USER variable
*                       in env)
*
*	w: word_to_be_updated
*/
void	mng_to_replace_env(char **w, t_x_y_word x_y, t_prompt **p, int **dict)
{
	int		len_val;
	char	*tmp_val;

	len_val = ft_strlen(ft_getenv_local((*p)->vars,
				get_word_2(*w, x_y))->val);
	tmp_val = malloc(sizeof(char) * (len_val + 1));
	tmp_val[len_val] = '\0';
	cpy_to_val ((ft_getenv_local((*p)->vars,
				get_word_2(*w, x_y)))->val, &tmp_val);
	replace_env(w, x_y, tmp_val, dict);
}

void	fill_with_nine(int **tmp_dict_quotes_word, int len)
{
	int	i;

	i = 0;
	while (len > 0)
	{
		(*tmp_dict_quotes_word)[i] = 9;
		i++;
		len--;
	}
}

/*get_len_pid
*
*	Returns:
*		-1: Error
*/
char	*ft_get_pid_str(void)
{
	char	*pid_str;
	int		pid;

	pid = ft_get_pid_int(0, 0, 0);
	pid_str = basic_itoa(pid);
	return (pid_str);
}
