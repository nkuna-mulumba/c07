/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 13:43:52 by jcongolo          #+#    #+#             */
/*   Updated: 2025/07/31 18:40:03 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int ft_is_separator(char *charset, char c)
{
    int i;

    i = 0;
    while (charset[i])
    {
        if (charset[i] == c)
        {
            return(1);//Encontrado separador
        }
        i++;
    }
    return(0);//Nao encontrado separador
}


int ft_count_word(char *str, char   *charset)
{
    int count;
    int i;
    int is_word;

    i = 0;
    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
    {
        i++;
    }
    
    count = 0;
    is_word = 0;
    while (str[i])
    {
        if (ft_is_separator(charset, str[i]) == 0)
        {
            if (is_word == 0)
            {
                count++;
            }   
            is_word = 1;
        }
        else
        {
            is_word = 0;
        }
        i++;
    }
    return(count);
}

char    *ft_strncpy_alloc(char *src, int n)
{
    int     i;
    char    *dest;

    dest = malloc((n + 1) * sizeof(char));
    if (!dest)
    {
        return(NULL);
    }
    
    i = 0;
    while (i < n && src[i])
    {
        dest[i] = src[i];
        i++;
    }
    while (i < n)
    {
        dest[i] = '\0';
        i++;
    }
    return(dest);
}

void    ft_free_array(char **array)
{
    int i;
    
    i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);//libera o array de ponteiros
}

char    **ft_split(char *str, char *charset)
{
    int     count_word;
    char    **array;
    int     i;
    int     start;
    int     index_word;
    
    count_word = ft_count_word(str, charset);
    array = malloc((count_word + 1) * sizeof(char *));
    if (!array)
    {
        return(NULL);
    }

    i = 0;
    index_word = 0;
    while (str[i])
    {
        //Ignora separadores
        while (ft_is_separator(charset, str[i]))
        {
            i++;           
        }
    
        if (str[i])
        {
            start = i;
            // Avança até o fim da palavra
            while (!ft_is_separator(charset, str[i]))
            {
                i++;
            }
            array[index_word] = ft_strncpy_alloc(&str[start], i - start);
            if (!array[index_word])
            {
                ft_free_array(array);
                return(NULL);
            }
            index_word++;
        }
    }
    array[index_word] = NULL;
    return (array);
}


int main(void)
{
    char    **array;
    int     i;
    char    *str = "eu que";
    char    charset = ",";
       
    array = ft_split(str, charset);
    if (!array)
    {
        return(1);
    }

    i = 0;
    while (array[i] != NULL)
    {
        printf("%s\n", array[i]);
        i++;
    }
    
    ft_free_array(array);
    return(0);
}