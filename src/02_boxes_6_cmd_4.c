/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_6_cmd_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 13:53:21 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/18 21:58:38 by uxmancis         ###   ########.fr       */
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

	(*box)->what_to_take = malloc(sizeof(char) * (ft_strlen((*box)->input_substr) + 1));
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
