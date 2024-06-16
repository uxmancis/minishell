/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_6_cmd_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 10:46:55 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/24 18:24:44 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	mark_quotes(t_box **box)
{
	int	len_substr;
	int	i;

	len_substr = ft_strlen((*box)->input_substr);
	i = 0;
	while (len_substr > 0)
	{
		if (((*box)->input_substr[i] == '\'' || (*box)->input_substr[i] == '\"')
			&& (*box)->dict_quotes[i] == 0)
			(*box)->what_to_take[i] = 'Q';
		i++;
		len_substr--;
	}
}

/*is_empty_str_first_cmd
*
*	Returns:
*		-1: 2Qs found first thing along rest_info_potential_cmd
*		0: other content was found before 2Qs.
*
* 	2Qs = "" as first thing, command not found error.
*
*	Explanatory comments:
*		· Both R and W are ignored each time we find them.
*		· Both Y and Q are the scope we're interested in.
*				· Q: 1st quote is found
*					· i + 1 = Q: 2nd quote is found
*
*	Returns:
*		-1: 2Qs are found in first position of potential comand and args.
*		0: Other info was found before 2Qs
*/
int	is_empty_str_first_cmd(t_box **box)
{
	int	len_substr;
	int	keep_len_substr;
	int	i;

	len_substr = ft_strlen((*box)->input_substr);
	keep_len_substr = ft_strlen((*box)->input_substr);
	i = 0;
	while (len_substr > 0)
	{
		while (i < keep_len_substr && ((*box)->what_to_take[i] == 'R'
				|| (*box)->what_to_take[i] == 'W'))
			i++;
		while (i < keep_len_substr && ((*box)->what_to_take[i] == 'Y'
				|| (*box)->what_to_take[i] == 'Q'))
		{
			if ((*box)->what_to_take[i] == 'Q')
			{
				if ((i + 1) < keep_len_substr
					&& (*box)->what_to_take[i + 1] == 'Q')
					return (-1);
			}
			else if ((*box)->what_to_take[i] == 'Y'
				&& !ft_isspace((*box)->input_substr[i]))
				return (0);
			i++;
		}
		i++;
		len_substr--;
	}
	return (0);
}

/*  ft_get_what_to_take
*
*   what_to_take variable will have the following info about
*   input_substr:
*
*       R: Redirección
*       W: Word : end delimiter, infile or outfile name. 1st word after red.
*       Y: YES take it as command and arguments to be analysed.
*
*	Return:
*		-1: Error: command not found. "" or '' as first command.
*		0: Success
*
*	init_what_to_take: 1st, what_to_take is completely initialized with 'Y'.
*/
int	ft_get_what_to_take(t_box **box)
{
	int	len;
	int	i;

	(*box)->what_to_take = malloc(sizeof(char)*(ft_strlen((*box)->input_substr)+1));
	(*box)->what_to_take[ft_strlen((*box)->input_substr)] = '\0';
	init_what_to_take(box);
	mark_redir(box);
	mark_word(box);
	mark_quotes(box);
	if (is_empty_str_first_cmd(box) == -1)
	{
		ft_puterror("Command '' not found\n");
		return (-1);
	}
	//Print result of_what_to_take:
	len = ft_strlen((*box)->input_substr);
	i = 0;
	printf("     what_to_take: len = %d\n", len);
	while (len > 0)
	{
		printf("               what_to_take[%d] = %c\n", i, (*box)->what_to_take[i]);
		len--;
		i++;
	}
	return (0);
}

/*cpy_rest_words
*
*	tmp_nb: Number of rest of words
*/
void	cpy_rest_words(t_box **box)
{
	int	tmp_nb;
	int	i;

	tmp_nb = (*box)->nb_of_words_rest;
	printf("     cpy_rest_words, nb_of_words_rest = %d\n", tmp_nb);
	(*box)->rest_info_potential_cmd = malloc(sizeof(char *) * (tmp_nb + 1));
	(*box)->rest_info_potential_cmd[tmp_nb] = malloc(sizeof(char) * 1);
	(*box)->rest_info_potential_cmd[tmp_nb][0] = '\0';
	i = 0;
	while (tmp_nb > 0)
	{
		cpy_1_word(box, i);
		tmp_nb--;
		i++;
	}
}

void	ft_get_only_needed(t_box **box)
{
	//int len_rest;
	//int i;
	//printf("micasa = %s\n", (*box)->micasa);
	printf("     ft_get_only_needed\n");
	(*box)->nb_of_words_rest = rest_numof_words(box);
	printf("               rest_numof_words | counter = "MAGENTA"%d\n"RESET_COLOR, (*box)->nb_of_words_rest);
	rest_get_ind_beginning_words(box);
	cpy_rest_words(box);
    /*len_rest = get_len_only_needed(box);
    (*box)->rest_info_potential_cmd = malloc(sizeof(char *) * (len_rest + 1))
    (*box)->rest_info_potential_cmd[len_rest] = '\0';
    i = 0;
    while (len_rest > 0)
    {
        
    }*/
}

/*ft_get_cmd_args
*
*	Returns:
*		-1: error management
*		0: Success
*
*	Comment: we'll only check dollars if there is min. 1 word to analyse
*/
int	ft_get_cmd_args(t_box **box, t_prompt **prompt)
{
	if (ft_get_what_to_take(box) == -1)
		return (-1);
	printf(MAGENTA"     char *what_to_take"RESET_COLOR" generated✅\n");
	ft_get_only_needed(box);
	//printf("nb_of_words_rest = %d\n", (*box)->nb_of_words_rest);
	//if ((*box)->nb_of_words_rest > 0) //ahora lo vamos a llamar siempre para checkear: infile, outfile_str, outfille_app, rest_words
	check_dollars_expansion(box, prompt);
	return (0);
}

/*ft_cmd_args
*
*	Returns:
*		-1: Error management
*		0: Success
*/
int	ft_cmd_args (t_box **box, t_prompt **prompt)
{
	printf("     02_boxes_6_cmd.c - "MAGENTA"ft_cmd_args\n"RESET_COLOR);
	if (ft_get_cmd_args(box, prompt) == -1)
		return (-1);
	return (0);
}
