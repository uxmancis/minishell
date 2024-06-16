/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   probatxue.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 09:10:28 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/16 09:28:13 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

typedef struct s_data
{
    char *str_name;
    char *str_lastname;
}   t_data;

void change_name(t_data *person1)
{
    //t_data new;

    //printf("Before str: %s\n", *str);
    //1. Free old
    if (person1->str_name)
        free (person1->str_name);
    if (person1->str_lastname)
        free (person1->str_lastname);

    //2. Generate new
    person1->str_name = malloc(sizeof(char) * 6);
    person1->str_name[0] = 'm';
    person1->str_name[1] = 'a';
    person1->str_name[2] = 'i';
    person1->str_name[3] = 't';
    person1->str_name[4] = 'e';
    person1->str_name[5] = '\0';

    person1->str_lastname = malloc(sizeof(char) * 6);
    person1->str_lastname[0] = 'l';
    person1->str_lastname[1] = 'a';
    person1->str_lastname[2] = 's';
    person1->str_lastname[3] = 'k';
    person1->str_lastname[4] = 'u';
    person1->str_lastname[5] = '\0';
    
    //3. Assign new value
    //*str = name.str2;
    //printf("After str: %s\n", *str);
}

int main(void)
{
    t_data person1;
    
    char *str_name;
    char *str_lastname;

    str_name = malloc(sizeof(char) * 5);
    str_name[0] = 'u';
    str_name[1] = 'x';
    str_name[2] = 'u';
    str_name[3] = 'e';
    str_name[4] = '\0';

    str_lastname = malloc(sizeof(char) * 6);
    str_lastname[0] = 'm';
    str_lastname[1] = 'a';
    str_lastname[2] = 'n';
    str_lastname[3] = 'c';
    str_lastname[4] = 'i';
    str_lastname[5] = '\0';

    person1.str_name = str_name;
    person1.str_lastname = str_lastname;

    printf("Before person1 name: %s\n", person1.str_name);
    printf("Before person1 lastname: %s\n", person1.str_lastname);
    change_name(&person1);
    printf("After person1 name: %s\n", person1.str_name);
    printf("After person1 lastname: %s\n", person1.str_lastname);
    return (0);
}