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

#include <stdlib.h>
int *ft_range(int min, int max)
{
    int len;
    int *array;
    int i;

    if (min >= max)
    {
        return(0);
    }
    
    len = max - min;
    array = malloc(len  * sizeof(int));
    if (!array)
    {
        return(0);
    }
    i = 0;
    while (i < len)//4,
    {
        array[i] = min;//1,2,3,4
        min++;//2,3,4
        i++;//1,2,3,4
    }
    return(array);
}
