//funciones que finalmente no necesito o cuyas versiones anteriores quiero tener almacenadas


//int ft_quotes(char *input, char **dictionary)
{
    int i;
    //int *dictionary; 

    i = 0;
    printf(RED);
    printf(">> entrada en bucle - análisis comillas\n");
    printf(RESET_COLOR);
    //dictionary = malloc(sizeof(int)*ft_strlen(input));
    while (input[i] != '\0')
    {
        if (input[i] == '\'')
        {
            printf(YELLOW);
            printf("        ENTRADA comillas simples, input[%d] = %c\n", i, input[i]);
            printf(RESET_COLOR);
            (*dictionary)[i] = '0'; //comillas principales (simples) están fuera de comillas
            i++;
            printf("i++, line 29, input[%d] = %c\n", i, input[i]);
            while (input[i] != '\0' && input[i] != '\'')
            {
                printf("             dentro comillas simples, input[%d] = %c\n", i, input[i]);
                (*dictionary)[i] = '1'; //dentro de comillas simples
                i++;
                printf("             i++, line 33, input[%d] = %c\n", i, input[i]);
            }
            printf(YELLOW);
            printf("        SALIDA comillas simples, input[%d] = %c\n\n", i, input[i]);
            printf(RESET_COLOR);
            //i++;
            //printf("             i++, line 42, input[%d] = %c\n", i, input[i]);
            if (i == (int)ft_strlen(input))
                    return (-1); //Error: unclosed quotes
        }
        if (input[i] == '\"')
        {
            printf(MAGENTA);
            printf("        ENTRADA comillas DOBLES, input[%d] = %c\n", i, input[i]);
            printf(RESET_COLOR);
            (*dictionary)[i] = '0'; //comillas principales (dobles) están fuera de comillas
            i++;
            while (input[i] != '\0' && input[i] != '\"')
            {
                printf("             dentro comillas DOBLES, input[%d] = %c\n", i, input[i]);
                (*dictionary)[i] = '2'; //dentro de comillas dobles
                i++;
                printf("             i++, line 44, input[%d] = %c\n", i, input[i]);
                if (i == (int)ft_strlen(input))
                    return (-1); //Error: unclosed quotes
            }
            printf(MAGENTA);
            printf("        SALIDA comillas DOBLES, input[%d] = %c\n\n", i, input[i]);
            printf(RESET_COLOR);
            //i++;
            //printf("             i++, line 60, input[%d] = %c\n", i, input[i]);
        }
        (*dictionary)[i] = '0'; //fuera de comillas
        i++;
        if (i != (int)ft_strlen(input)) //solo para printear. Sin este if nos imprime un caracter de más, yendo ya más allá de la cadena "input". Eso ya no quiero que me lo imprimas.
            printf("i++, line 49, input[%d] = %c\n", i, input[i]);
    }
    printf(GREEN);
    printf("<< salida de bucle - análisis comillas\n");
    printf(RESET_COLOR);
    return (0); //Success, quotes properly closed and dictionary created
}

/*ft_count_len
*   Returns real needed len for the input we are going to handle.
*   Calculates the amount of char spaces we will need to allocate
*   input without unnecessary spaces.
*/
int ft_count_len(char *input)
{
    int counter;
    int i; 

    counter = 0;
    i = 0;
    while (input[i] != '\0')
    {
        if (input[i] == '\'')
        {
            counter++; //contar comilla
            //printf("counter++, line 104, input[%d] = %c\n", i, input[i]);
            i++;
            while(input[i] != '\'')
            {
                if (input[i] != ' ')
                {
                    counter++;
                    //printf("counter++, line 99, input[%d] = %c\n", i, input[i]);
                }
                i++;
            }
            //i++; //para salir de comillas
            //counter++;
            //printf("counter++, line 104, input[%d] = %c\n", i, input[i]);
        }
        if (input[i] == '\"')
        {
            counter++; //contar comilla
            //printf("counter++, line 104, input[%d] = %c\n", i, input[i]);
            i++;
            while(input[i] != '\"')
            {
                if (input[i] != ' ')
                {
                    counter++;
                    //printf("counter++, line 114, input[%d] = %c\n", i, input[i]);
                }
                i++;
            }
            //i++; //para salir de comillas
            //counter++;
            //printf("counter++, line 119, input[%d] = %c\n", i, input[i]);
        }
        counter++;
        //printf("counter++, line 122, input[%d] = %c\n", i, input[i]);
        i++;
    }
    return (counter);
}


char *ft_cpy_clean_input(char *input, char **clean_input, int len)
{
    int i_new; //index to iterate through char **clean_input
    int i_old; //index to iterate through char *input
    int flag; //1 = comilla simple, 2 = comilla doble

    i_new = 0;
    i_old = 0;
    flag = 1;
    (void)len;
    //(*clean_input)[len - 1] = '\0';
    while ((*clean_input)[i_new] != '\0')
    {
        while (input[i_old] != '\'' || input[i_old] != '\"' ) //hasta llegar a comillas, copialo todo
        {
            (*clean_input)[i_new] = input[i_old];
            i_new++;
            i_old++;
        }
        if (input[i_old] == '\''||input[i_old] == '\"') //si es uno u otro
        {
            if (input[i_old] == '\"') //si se trata de dobles, actualizamos el flag
                flag = 2;
            (*clean_input)[i_new] = input[i_old];
            i_new++;
            i_old++;
            if (flag == 1)
            while(input[i_old] != '\'') //hasta que vuelva a salir la comilla
            {
                if (input[i_old] != ' ') //si no es un espacio
                {
                    (*clean_input)[i_new] = input[i_old];
                    i_new++;
                }
                i_old++; //si no (o, en cualquier caso, sea o no espacio), simplemente vete avanzando
            }
            else if (flag == 2)
            while(input[i_old] != '\"') //hasta que vuelva a salir la comilla
            {
                if (input[i_old] != ' ') //si no es un espacio
                {
                    (*clean_input)[i_new] = input[i_old];
                    i_new++;
                }
                i_old++; //si no (o, en cualquier caso, sea o no espacio), simplemente vete avanzando
            }
        }
    }
    return (*clean_input);
}

/*ft_no_spaces
*   takes out unnecessary spaces from input.
*   If spaces are outside of quotes are eliminared.
*   Spaces inside quotes are kept.
*   
*   Returns: new clean_input without unnecessary spaces.
*/
char *ft_no_spaces(char *input)
{
    int new_len;
    char *clean_input;

    printf("old_len = %d\n", (int)ft_strlen(input));
    new_len = ft_count_len(input);
    printf("new_len = %d\n", new_len);    
    clean_input = malloc(sizeof(char)*new_len);
    clean_input[new_len - 1] = '\0';
    clean_input = ft_cpy_clean_input(input, &clean_input, new_len);
    //temporal
    int i; 
    i = 0;
    while (clean_input[i] != '\0')
    {
        clean_input[i] = 'a';
        i++;
    }
    return (clean_input);
}