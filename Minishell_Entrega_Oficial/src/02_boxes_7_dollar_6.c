/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_7_dollar_6.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:59:29 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/31 17:59:58 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

/*Checks whether if dollar is found outside of quotes
*   or inside double quotes (inside single quotes is a no).
*
*   I could just say tmp_dict_quotes[i] != 1.
*   I just feel == 0 || == 2 is a little safer though.
*
*   tmp_to_compare = (*box)->rest_info_potential_cmd word, but
*   the updated version. P.ej.: imagine it's already been updated 
*   because ofother dollars before
*/
int is_dollar(t_box **box, t_x_y_rest_info x_y, int **tmp_dict_quotes)
{
    //printf("     "YELLOW"is_dollar"RESET_COLOR" | rest_info_potential_cmd[%d][%d] = %c\n", x_y.index_x, x_y.index_y, (*box)->rest_info_potential_cmd[x_y.index_x][x_y.index_y]);
    //printf("     tmp_dict_quotes[%d]= %d\n", x_y.index_y, (*tmp_dict_quotes)[x_y.index_y]);
    //if (tmp_to_compare[x_y.index_y] == '$' && (tmp_dict_quotes[x_y.index_y] == 0 || tmp_dict_quotes[x_y.index_y] == 2))
    if ((*box)->rest_info_potential_cmd[x_y.index_x][x_y.index_y] == '$' && ((*tmp_dict_quotes)[x_y.index_y] == 0 || (*tmp_dict_quotes)[x_y.index_y] == 2))
        return (1);
    return (0);
}

int next_is_space_or_end (t_box **box, t_x_y_rest_info x_y)
{
    int len_word;

    len_word = ft_strlen((*box)->rest_info_potential_cmd[x_y.index_x]);
    if (x_y.index_y == len_word - 1) //END: $ in las position
        return (1);
    if ((x_y.index_y + 1) < len_word) //SPACE: si todavía sí hay más posiciones (a way to prevent overflow), then check if próxima posición es un ' '
    {
        if ((*box)->rest_info_potential_cmd[x_y.index_x][x_y.index_y + 1] == ' ')
            return (1);
    }
    return (0);
}

int next_is_sec_dollar(t_box **box, t_x_y_rest_info x_y)
{
    int len_word;

    //printf("next_is_sec_dollar | rest_info_potential_cmd[%d][%d] = %c\n", x_y.index_x, x_y.index_x, (*box)->rest_info_potential_cmd[x_y.index_x][x_y.index_y]);
    len_word = ft_strlen((*box)->rest_info_potential_cmd[x_y.index_x]);
    if ((x_y.index_y + 1) < len_word) //a way to prevent overflow
    {
        if ((*box)->rest_info_potential_cmd[x_y.index_x][x_y.index_y + 1] == '$')
        {
            //printf("                         second dollar identified!\n");
            return (1);
        }
    }
    //printf("                         no second dollar\n");
    return (0);
}

void cpy_word (char *str_src, char **str_dst)
{
    int len;
    int i;

    len = ft_strlen(str_src);
    i = 0;
    while (len > 0)
    {
        (*str_dst)[i] = str_src[i];
        i++;
        len--;
    }
    //printf("               str_dst = "YELLOW"%s\n"RESET_COLOR, *str_dst);
}

int get_len_pid (t_box **box)
{
    //pid_t pid;
    int len_process_pid;

    (*box)->tmp_pid = getpid();
    (*box)->tmp_pid_str = basic_itoa((*box)->tmp_pid);
    len_process_pid = ft_strlen((*box)->tmp_pid_str);
    return (len_process_pid);
}