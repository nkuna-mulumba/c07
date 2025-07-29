/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:04:27 by jcongolo          #+#    #+#             */
/*   Updated: 2025/07/29 16:58:14 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
    * Reimplementa a função strdup.
    * Cria uma nova string duplicando o conteúdo de `src` usando
        alocação dinâmica.
    * Funções autorizadas: malloc
*/

#include <stdlib.h>
char    *ft_strdup(char *src)
{
    int     len_src;
    char    *dup_src;
    int     i;

    len_src = 0;
    while (src[len_src])
    {
        len_src++;
    }
    
    dup_src = malloc((len_src + 1) * sizeof(char));
    if (!dup_src)
    {
        return(0);
    }
    
    i = 0;
    while (src[i])
    {
        dup_src[i] = src[i];
        i++;
    }
    dup_src[i] = '\0';

    return(dup_src);
}

/*
    #include <stdio.h>
    int main(void)
    {
        char    *src = "abcdef";
        char    *dup_src = NULL;
        printf("ANTES -> src = %s e dup_src = %s\n", src, dup_src);
        
        dup_src = ft_strdup(src);
        printf("DEPOIS -> src = %s e dup_src = %s\n", src, dup_src);
        free(dup_src);
        return(0);
    }
*/