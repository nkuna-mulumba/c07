/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:54:37 by jucongol          #+#    #+#             */
/*   Updated: 2025/07/30 17:13:37 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>

/*
    ft_empty_string - Cria e retorna uma string vazia ("").
    Objetivo:
        Utilizada quando a função ft_strjoin recebe size = 0
        para retornar uma string válida e segura (em vez de NULL).
    Parâmetros:
        (nenhum)
    Retorno:
        - Ponteiro para string vazia alocada dinamicamente
        - NULL em caso de falha no malloc
    Comportamento:
        - Aloca 1 byte e armazena apenas o '\0'
*/
char    *ft_empty_string(void)
{
    char    *str;

    str = malloc(sizeof(char));
    if(!str)
    {
        return(NULL);
    }
    *str = '\0';
    return(str);
}

/*
    ft_strlen - Calcula o comprimento de uma string.
    Objetivo:
        Utilizada para saber o espaço necessário ao juntar várias strings.
    Parâmetros:
        str → ponteiro para uma string de caracteres
    Retorno:
        - Número de caracteres antes do '\0'
    Comportamento:
        - Itera pela string contando até o final ('\0')
*/
int ft_strlen(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        i++;
    }
    return(i);
}

/*
    ft_strcat - Concatena a string 'src' no final da string 'dest'.
    Objetivo:
        Criada para montar uma única string a partir de várias outras.
        É utilizada em ft_strjoin para construir a string final concatenada.
    Parâmetros:
        dest → string de destino (modificada no final)
        src → string de origem (copiada para o final de dest)
    Retorno:
        - Ponteiro para 'dest' após concatenação
    Comportamento:
        - Encontra o final de 'dest'
        - Copia 'src' caractere por caractere após esse ponto
        - Finaliza com o terminador nulo '\0'
*/
char   *ft_strcat(char *dest, char *src)
{
    int len_dest;
    int i;

    len_dest = 0;
    while(dest[len_dest])
    {
        len_dest++;
    }
    i = 0;
    while(src[i])
    {
        dest[len_dest] = src[i];
        len_dest++;
        i++;
    }
    dest[len_dest] = '\0';
    return(dest);
}

/*
    ft_strjoin - Junta várias strings com um separador entre elas.
    Parâmetros:
        size → número de strings no array strs
        strs → array de ponteiros para strings a serem concatenadas
        sep → string separadora a ser inserida entre cada elemento
    Retorno:
        - Ponteiro para a string final concatenada
        - String vazia se size for 0
        - NULL em caso de falha na alocação
    Comportamento:
        - Calcula o tamanho total necessário para a nova string
        - Aloca memória suficiente para todas as strings + separadores + '\0'
        - Concatena as strings na ordem, separando com 'sep'
*/
char    *ft_strjoin(int size, char **strs, char *sep)
{
    int     index_strs;
    long    len_strs;
    char    *str;

    if(size <= 0)
    {
        return(ft_empty_string());//Retornar '\0', se não houver strings
    }
  
    index_strs = 0;
    len_strs = 0;
    //Somar os comprimentos de todas strings
    while(index_strs < size)
    {
        len_strs = len_strs + ft_strlen(strs[index_strs]);
        index_strs++;
    }

    //Alocar espaço para todas strings, separadores e o '\0'
    str = malloc(len_strs + ft_strlen(sep) * (size - 1) + 1);
    if(!str)
    {
        return(NULL);
    }
    
    str[0] = '\0';
    ft_strcat(str, strs[0]);//Começar com a primeira string
    
    //Concatenar cada string com seu separador
    index_strs = 1;
    while(index_strs < size)
    {
        ft_strcat(str, sep);
        ft_strcat(str, strs[index_strs]);
        index_strs++;
    }
    return(str);//Retornar string final concatenada
}


/*
    //Passar argumentos no main:
    #include <stdio.h>
    int main(void)
    {
        char    *strs[] = {"olá", "mundo", "juliao"};
        int     size = sizeof(strs) / sizeof(strs[0]);
        char    *result = ft_strjoin(size, strs, " | ");
        

        if (result != NULL)
        {
            printf("%s\n", result);
            free(result);
        }
        else
        {
            printf("Erro ao alocar memória\n");
        }
        return 0;
    }
*/


    //passar argumentos pelo terminal
    #include <stdio.h>
    int main(int argc, char **argv)
    {
        char    **strs = argv + 1; //Pula argv[0], que é o nome do programa
        int     size = argc - 2; //Excluir executavel e seprador
        char    *sep = argv[argc - 1]; //Ultimo argumento é o seprador
        char    *result = ft_strjoin(size, strs, sep);
        

        if (result != NULL)
        {
            printf("%s\n", result);
            free(result);
        }
        else
        {
            printf("Erro ao alocar memória\n");
        }
        return 0;
    }