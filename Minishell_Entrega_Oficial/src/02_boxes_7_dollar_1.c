/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_7_dollar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:31:14 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/26 18:51:02 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	expand_infile_words(t_box **box, t_prompt **prompt)
{
	int	tmp_nb_of_words_infile;
	int	nb_infile_x;

	printf("          which words are we checking?"YELLOW" - INFILE_WORDS\n"RESET_COLOR);
	tmp_nb_of_words_infile = (*box)->nb_of_infile;
	nb_infile_x = 0;
	(*box)->flag_word_or_cmd = 'W';
	while (tmp_nb_of_words_infile > 0)
	{
		get_each_word_up((*box)->words_infile[nb_infile_x], nb_infile_x, box, prompt);
		nb_infile_x++;
		tmp_nb_of_words_infile--;
	}
}

/*
*	About (*box)->flag_word_or_cmd = 'W':
*		It will be used in generate_specif_dict_quotes in order to know
*		which is index word, to know which is the index in dict_quotes we
*		wanna copy. It will impact in variable named "start".
*/
void	expand_outfile_strong_words(t_box **box, t_prompt **prompt)
{
	int	tmp_nb_of_words_outf_str;
	int	nb_outfile_str_x;

	printf("          which words are we checking?"YELLOW" - OUTFILE_STRONG_WORDS\n"RESET_COLOR);
	tmp_nb_of_words_outf_str = (*box)->nb_of_outfile_strong;
	nb_outfile_str_x = 0;
	(*box)->flag_word_or_cmd = 'W';
	while (tmp_nb_of_words_outf_str > 0)
	{
		get_each_word_up((*box)->words_outfile_strong[nb_outfile_str_x], nb_outfile_str_x, box, prompt);
		nb_outfile_str_x++;
		tmp_nb_of_words_outf_str--;
	}
}

/*
*	About (*box)->flag_word_or_cmd = 'W':
*		It will be used in generate_specif_dict_quotes in order to know
*		which is index word, to know which is the index in dict_quotes we
*		wanna copy. It will impact in variable named "start".
*/
void	expand_outfile_append_words(t_box **box, t_prompt **prompt)
{
	int	tmp_nb_of_words_outf_app;
	int	nb_outfile_app_x;

	printf("          which words are we checking?"YELLOW" - OUTFILE_APPEND_WORDS\n"RESET_COLOR);
	tmp_nb_of_words_outf_app = (*box)->nb_of_outfile_append;
	nb_outfile_app_x = 0;
	(*box)->flag_word_or_cmd = 'W';
	while (tmp_nb_of_words_outf_app > 0)
	{
		get_each_word_up((*box)->words_outfile_append[nb_outfile_app_x], nb_outfile_app_x, box, prompt);
		nb_outfile_app_x++;
		tmp_nb_of_words_outf_app--;
	}
}

/*
*	About (*box)->flag_word_or_cmd = 'W':
*		It will be used in generate_specif_dict_quotes in order to know
*		which is index word, to know which is the index in dict_quotes we
*		wanna copy. It will impact in variable named "start".
*/
void	expand_rest_info_potential_cmd(t_box **box, t_prompt **prompt)
{
	int	tmp_nb_of_words_rest_info;
	int	nb_word_rest_x;

	printf("          which words are we checking?"YELLOW" - REST_WORDS_POTENCIAL_CMD\n"RESET_COLOR);
	tmp_nb_of_words_rest_info = (*box)->nb_of_words_rest;
	nb_word_rest_x = 0;
	(*box)->flag_word_or_cmd = 'C';
	while (tmp_nb_of_words_rest_info > 0)
	{
		get_each_word_up((*box)->rest_info_potential_cmd[nb_word_rest_x], nb_word_rest_x, box, prompt);
		nb_word_rest_x++;
		tmp_nb_of_words_rest_info--;
	}
}

/*
*   Variables:
*       tmp_nb_of_words: nb_of_words_rest
*/
void	check_dollars_expansion(t_box **box, t_prompt **prompt)
{
	printf("----------------------------------------------\n\n");
	printf("     02_boxes_6_cmd.c - "YELLOW"check_dollars_expansion\n"RESET_COLOR);
	expand_infile_words(box, prompt);
	expand_outfile_strong_words(box, prompt);
	expand_outfile_append_words(box, prompt);
	expand_rest_info_potential_cmd(box, prompt);
}