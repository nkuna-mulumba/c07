/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:59:29 by jcongolo          #+#    #+#             */
/*   Updated: 2025/07/29 17:29:38 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
    ft_range - Cria um array de inteiros de min até (max - 1).
    Parâmetros:
        min → valor inicial do intervalo (inclusive)
        max → valor final do intervalo (exclusivo)
    Retorno:
        - Ponteiro para o array de inteiros alocado dinamicamente
        - NULL se min >= max ou em caso de falha na alocação
    Comportamento:
        - Aloca memória para (max - min) elementos
        - Preenche o array com valores crescentes, iniciando em min
*/
#include <stdlib.h>
int *ft_range(int min, int max)
{
    int len;
    int *array;
    int i;

    if (min >= max)
    {
        return(NULL);
    }
    
    len = max - min;

    array = malloc(len  * sizeof(int));
    if (!array)
    {
        return(NULL);
    }
    i = 0;
    while (i < len)
    {
        array[i] = min;
        min++;
        i++;
    }
    return(array);
}

/*
    #include <stdio.h>
    int main(void)
    {
        int min;
        int max;
        int len;
        int *array_int;
        int i;

        min = 1;
        max = 5;
        len = max - min;
        printf("Main->[%d]\n", len);
        array_int = ft_range(min, max);
        if(!array_int)
        {
            return(1);
        }

        i = 0;
        while(i < len)
        {
            printf("%d\n", array_int[i]);
            i++;
        }

        free(array_int);
        return(0);
    }
*/