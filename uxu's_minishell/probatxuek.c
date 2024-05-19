/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   probatxuek.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:00:20 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/19 13:09:14 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char *basic_itoa(int nb)
{
    char *str;
    int len;
    int keep_nb;
    int i;
    
    keep_nb = nb;
    len = 0;
    while (nb  > 10)
    {
        printf("Before nb = %d - ", nb);
        len++;
        nb = nb / 10;
        printf("After nb = %d\n", nb);
    }
    if (nb > 0 && nb < 10)
        len++;
    printf("len itoa = %d\n", len);
    str = malloc(sizeof(char) * (len + 1));
    str[len] = '\0';
    i = len - 1 ;
    while (len > 0) //copiarmos de dcha a izq.
    {
        str[i] = (keep_nb % 10) + 48;
        i--;
        keep_nb = keep_nb / 10;
        len--;
    }
    printf("result = %s\n", str);
}



int main(void)
{
    pid_t pid;

    pid = getpid();
    printf("pid = %d\n", pid);
    basic_itoa(pid);
    return (0);
}