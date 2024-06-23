/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   000_debug_mode_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:43:43 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 21:45:48 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	put_parsing_box_beginning(int substr_id, t_prompt *prompt, t_box **box)
{
	int	len;
	int	i;

	if (DEBUG_MODE == 0)
		return ;
	printf(BLUE"\n\n\n===ִ𓂃 ࣪˖ ִֶָ🐇་༘࿐==ᯓ★_⋆˚࿔ 📦BOX NB: %d 𝜗𝜚˚⋆", substr_id);
	printf("========𓇼🐚☾☼🦪========;༊;༊__\n"RESET_COLOR);
	printf("     02_boxes.c - "BLUE"ft_boxes_init"RESET_COLOR);
	printf(": Boxes are generated here. Nb_of_substr to be created");
	printf(" = "BLUE"%d"RESET_COLOR". Let's start!\n", prompt->nb_of_substr);
	len = ft_strlen((*box)->input_substr);
	i = 0;
	while (len > 0)
	{
		printf("               input_substr[%d] = ", i);
		printf("%c\n", (*box)->input_substr[i]);
		i++;
		len--;
	}
	printf("     02_boxes.c - ft_boxes_init| Copied!✅");
	printf(BLUE" input_substr"RESET_COLOR" generated:");
	printf(GREEN" %s", (*box)->input_substr);
	printf(RESET_COLOR", len = %d\n", (int)ft_strlen((*box)->input_substr));
}

void	put_parsing_box_dict_quotes(t_box **box)
{
	int	len;
	int	i;

	if (DEBUG_MODE == 0)
		return ;
	len = ft_strlen((*box)->input_substr);
	i = 0;
	while (len > 0)
	{
		printf("               dict_substr[%d] = ", i);
		printf("%d\n", (*box)->dict_quotes[i]);
		len--;
		i++;
	}
	printf("     02_boxes.c - ft_boxes_init|"BLUE);
	printf(" dict_quotes"RESET_COLOR" generated✅\n");
}

void	put_parsing_box_numof_redir(int counter)
{
	if (DEBUG_MODE == 0)
		return ;
	printf("     02_boxes_redir.c - ft_get_numof_redir| Counted!✅");
	printf(BLUE " nb_of_red = %d\n" RESET_COLOR, counter);
}

void	put_parsing_box_numof_redir_2(void)
{
	if (DEBUG_MODE == 0)
		return ;
	printf("     02_boxes_redir.c - " BLUE "set_red_index_type");
	printf(RESET_COLOR "| Info about redirecciones is stored here:\n");
}

void	put_parsing_box_numof_redir_3(t_box **box, int index_of_arr)
{
	if (DEBUG_MODE == 0)
		return ;
	printf(GREEN "               redirection %d", index_of_arr + 1);
	printf("assigned:     [0]_INDEX: %d",
		(*box)->dictred_i_t[index_of_arr][0]);
	printf("  [1]_TYPE: %s\n"RESET_COLOR,
		ft_enum_to_str((*box)->dictred_i_t[index_of_arr][1]));
}
