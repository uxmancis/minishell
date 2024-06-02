/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:45:31 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/02 11:20:00 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// // #include "../inc/minishell.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>


// // int ft_strlen(char *str)
// // {
// //     int i;
// //     int len;

// //     i = 0;
// //     len = 0;
// //     while (str[i] != '\0')
// //     {
// //         i++;
// //         len++;
// //     }
// //     return (len);
// // }

// /*ft_strcmp_2
// *
// *   Returns:
// *       1: yes str are exactly the same
// *       0: not same str
// */
// int ft_strcmp_2(char *str_2_check, char *cmd)
// {
//     int i;
//     int len_str_2_check;
//     int len_cmd;

//     len_str_2_check = ft_strlen(str_2_check);
//     len_cmd = ft_strlen(cmd);
//     i = 0;
//     //printf("len 1 = %d, len 2 = %d\n", len_str_2_check, len_cmd);

//     if (len_str_2_check != len_cmd)
//         return (0);
//     else if (len_str_2_check == len_cmd)
//     {
//         while (len_cmd > 0)
//         {
//             //printf("we're checking: str_2_check[%d] = %c, and cmd[%d] = %c\n", i, str_2_check[i], i, cmd[i]);
//             if (str_2_check[i] != cmd[i])
//             {
//                 //printf("NO match");
//                 return (0);
//             }
                
//             i++;
//             len_cmd--;
//         }        
//     }
//     //printf("MATCH! ");
//     return (1);
// }

// void ft_putchar(char c)
// {
//     //printf("%c", c);
//     write(1, &c, 1);
// }

// // void ft_putstr (char *str)
// // {
// //     printf("%s", str);
// // }


// /* put_without_next_line
// *
// *   Used when e.g. echo -n hola (echo with no -n flag)
// *   Prints: hola
// */
// //void put_without_next_line (t_box **box)
// void put_without_next_line (char **rest_info, int nb_of_words)
// {
//     int x;
//     int y;

//     printf("put_withOUT_next_line\n");
//     x = 2;
//     //while ((*box)->rest_info_potential_cmd[x] != '\0')
//     while (x < nb_of_words)
//     {
//         y = 0;
//         //while ((*box)->rest_info_potential_cmd[x][y] != '\0')
//         while (rest_info[x][y] != '\0')
//         {
//             //ft_putchar((*box)->rest_info_potential_cmd[x][y]);
//             ft_putchar(rest_info[x][y]);
//             y++;
//         }
//         x++;
//     }
// }

// /* put_with_next_line
// *
// *   Used when e.g. echo hola (echo with no -n flag)
// *   Prints: hola\n
// */
// //void put_with_next_line (t_box **box)
// void put_with_next_line (char **rest_info, int nb_of_words)
// {
//     int x;
//     int y;

//     printf("put_with_next_line\n");
//     x = 1;
//     //while ((*box)->rest_info_potential_cmd[x] != '\0')
//     //while (rest_info[x] != '\0')
//     while (x < nb_of_words)
//     {
//         y = 0;
//         //while ((*box)->rest_info_potential_cmd[x][y] != '\0')
//         while (rest_info[x][y] != '\0')
//         {
//             ///ft_putchar((*box)->rest_info_potential_cmd[x][y]);
//             ft_putchar(rest_info[x][y]);
//             y++;
//         }
//         x++;
//     }
//     printf("\n");
//     //ft_putchar('\n');
// }

// /*ft_builtin_echo
// *
// *   echo is a command required to build by 42 cursus Minishell project.
// *
// *   echo command displays a line of text in standard output.
// */
// //void ft_builtin_echo (t_box **box)
// void ft_builtin_echo (char **rest_info, int nb_of_words)
// {
//     //if (ft_strcmp_2((*box)->rest_info_potential_cmd)[1], "-n")
//     if (ft_strcmp_2(rest_info[1], "-n"))
//     {
//         printf("\n-n found\n");
//         put_without_next_line(rest_info, nb_of_words);
//         //put_without_next_line(box);
//     }
//     else
//     {
//         printf("\n-n NOT found\n");
//         put_with_next_line(rest_info, nb_of_words);
//     }
//     //put_with_next_line(box);
// }


// /*ft_builtin_pwd
// *
// *   pwd is a command required to build by 42 cursus Minishell project.
// *
// *   pwd command prints the name of current/working directory.
// *   Information is taken from environment. We've implemented it using
// *   linked list.
// */
// // void ft_builtin_pwd(t_prompt **prompt)
// // {
// //     ft_putstr(ft_getenv_local((*prompt)->vars, "PWD")->val);
// //     //ft_putchar("\n");
// //     printf("\n");
// // }

// /*which_cmd
// *
// *   Return is used as a way to finish function execution.
// */
// //int which_cmd(t_box **box, t_prompt **prompt)
// int which_cmd(char **rest_info, int nb_of_words)
// {
//     printf(">> which_cmd\n");
//     // (void)prompt;
//     //si no hay nada en esta variable, no tenemos que chequearlo
//     //if (!(*box)->rest_info_potential_cmd)
//     //if ((int)ft_strlen((*box)->rest_info_potential_cmd[1]) == 0)
    
//     //TMP, gero berriz jarri
//     // if ((*box)->nb_of_words_rest == 0)
//     //     return (-1);
//     // if (!(*box)->rest_info_potential_cmd)
//     // {
//     //     ft_putstr(": command not found\n");
//     //     return (0);
//     // }
//     // ----------------------------------
    
//     //else if (ft_strcmp_2((*box)->rest_info_potential_cmd[0], "echo"))
    
//     if (ft_strcmp_2(rest_info[0], "echo"))
//     {
//         printf("echo was identified");
//         ft_builtin_echo(rest_info, nb_of_words); //ft_builtin_echo(box);
//         //printf("done\n");
//     }
//     else if (ft_strcmp_2(rest_info[0], "pwd"))//else if (ft_strcmp_2((*box)->rest_info_potential_cmd[0], "pwd"))
//     {
//         printf("pwd was detected\n");
//         //ft_builtin_pwd(prompt);
//     }
//     else if (ft_strcmp_2(rest_info[0], "cd"))//else if (ft_strcmp_2((*box)->rest_info_potential_cmd[0], "pwd"))
//     {
//         printf("cd was detected\n");
//         //ft_builtin_pwd(prompt);
//     }
//     else if (ft_strcmp_2(rest_info[0], "exit"))//else if (ft_strcmp_2((*box)->rest_info_potential_cmd[0], "pwd"))
//     {
//         printf("exit was detected\n");
//         //ft_builtin_pwd(prompt);
//     }
//     else if (ft_strcmp_2(rest_info[0], "unset"))//else if (ft_strcmp_2((*box)->rest_info_potential_cmd[0], "pwd"))
//     {
//         printf("unset was detected\n");
//         //ft_builtin_pwd(prompt);
//     }
//     else if (ft_strcmp_2(rest_info[0], "export"))//else if (ft_strcmp_2((*box)->rest_info_potential_cmd[0], "pwd"))
//     {
//         printf("export was detected\n");
//         //ft_builtin_pwd(prompt);
//     }
//     else if (ft_strcmp_2(rest_info[0], "env"))//else if (ft_strcmp_2((*box)->rest_info_potential_cmd[0], "pwd"))
//     {
//         printf("env was detected\n");
//         //ft_builtin_pwd(prompt);
//     }
         
//     // // else if (ft_strcmp_2((*box)->rest_info_potential_cmd[0], "cd"))
//     // else if (ft_strcmp_2((*box)->rest_info_potential_cmd[0], "exit"))
//     // else if (ft_strcmp_2((*box)->rest_info_potential_cmd[0], "unset"))
//     // else if (ft_strcmp_2((*box)->rest_info_potential_cmd[0], "export"))
//     // else if (ft_strcmp_2((*box)->rest_info_potential_cmd[0], "env"))
//     // else
//     // {
//         // ft_putstr((*box)->rest_info_potential_cmd[0]);
//         // ft_putstr(": command not found\n");
//     // }
//     return (0);
// }

// int main(void)
// {
//     char **rest_info_potential_cmd;
//     int nb_of_words;

//     nb_of_words = 4;
//     rest_info_potential_cmd = malloc(sizeof(char *) * nb_of_words);
//     rest_info_potential_cmd[0] = malloc(sizeof(char)*(5));
//     rest_info_potential_cmd[0][0] = 'e';
//     rest_info_potential_cmd[0][1] = 'c';
//     rest_info_potential_cmd[0][2] = 'h';
//     rest_info_potential_cmd[0][3] = 'o';
//     rest_info_potential_cmd[0][4] = '\0';

//     rest_info_potential_cmd[1] = malloc(sizeof(char)*(3));
//     rest_info_potential_cmd[1][0] = '-';
//     rest_info_potential_cmd[1][1] = 'n';
//     rest_info_potential_cmd[1][2] = '\0';
    
//     rest_info_potential_cmd[2] = malloc(sizeof(char)*(5));
//     rest_info_potential_cmd[2][0] = 'h';
//     rest_info_potential_cmd[2][1] = 'o';
//     rest_info_potential_cmd[2][2] = 'l';
//     rest_info_potential_cmd[2][3] = 'a';
//     rest_info_potential_cmd[2][4] = '\0';

//     rest_info_potential_cmd[3] = malloc(sizeof(char)*(4));
//     rest_info_potential_cmd[3][0] = 'u';
//     rest_info_potential_cmd[3][1] = 'x';
//     rest_info_potential_cmd[3][2] = 'u';
//     rest_info_potential_cmd[3][3] = '\0';
//     //get_rest_info(&rest_info_potential_cmd, nb_of_words);
//     //printf("str checking: pwd\n");
//     which_cmd(rest_info_potential_cmd, nb_of_words);
    
//     free(rest_info_potential_cmd[0]);
//     free(rest_info_potential_cmd[1]);
//     free(rest_info_potential_cmd[2]);
//     free(rest_info_potential_cmd[3]);
//     free(rest_info_potential_cmd);
//     return (0);
// }