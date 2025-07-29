/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_range.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucongol <jucongol@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-29 18:33:20 by jucongol          #+#    #+#             */
/*   Updated: 2025-07-29 18:33:20 by jucongol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
    ft_ultimate_range - Aloca um array de inteiros entre min e max.
    Parâmetros:
        range → ponteiro para onde será armazenado o array alocado
        min → valor inicial do intervalo (inclusive)
        max → valor final do intervalo (exclusivo)
    Retorno:
        - Tamanho do array alocado (max - min)
        - 0 se min >= max (range recebe NULL)
        - -1 em caso de falha na alocação (range recebe NULL)
    Comportamento:
        - Aloca memória para (max - min) inteiros
        - Preenche o array com valores crescentes iniciando em min
        - Entrega o ponteiro para o array via argumento range
*/
#include <stdlib.h>
int ft_ultimate_range(int **range, int min, int max)
{
    int len;
    int *array;
    int i;

    if(min >= max)
    {
        *range = NULL;   
        return(0);
    }

    len = max - min;

    array = malloc(len * sizeof(int));
    if(!array)
    {
        *range = NULL;
        return(-1);
    }

    i = 0;
    while(i < len)
    {
        array[i] = min;
        min++;
        i++;
    }

    *range = array;
    return(len);
}

/*
    #include <stdio.h>
    int main(void)
    {
        int min;
        int max;
        int len;
        int *array;
        int i;

        min = 1;
        max = 5;
        len = ft_ultimate_range(&array, min, max);
        if(len == -1)
        {
            printf("Erro de alocar\n");
        }
        else if(len == 0)
        {
            printf("Range do array vazio: %d >= %d\n", min, max);
        }

        printf("Tamanho do array: %d\n", len);
        i = 0;
        while(i < len)
        {
            printf("array[%d] = %d\n", i, array[i]);
            i++;
        }
        free(array);
        return(0);
    }
*/
