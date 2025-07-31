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

/*
    * ft_is_separator
    * Função auxiliar que verifica se o caractere 'c' é um dos separadores
        definidos em 'charset'.
    * Implementada para facilitar a lógica de detecção de palavras na
    string principal.
*/
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

/*
    * ft_count_word
    * Conta quantas palavras estão presentes em 'str', separadas por qualquer 
        caractere de 'charset'.
    * Serve para saber quantas alocações serão necessárias para o 
        array de strings.
    * Ignora espaços e separadores consecutivos — evita criar 
        substrings vazias.
*/
int ft_count_word(char *str, char   *charset)
{
    int count;
    int i;
    int is_word;

    //Pular espaços iniciais e tabulações
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
                count++;//Início de nova palavra
            }   
            is_word = 1;
        }
        else
        {
            is_word = 0;//Encontrou separador
        }
        i++;
    }
    return(count);
}

/*
    * ft_strncpy_alloc
    * Aloca uma nova string com 'n' caracteres de 'src' e adiciona o
        caractere nulo no final.
    * Usada para extrair palavras de dentro de 'str' e criar cópias
        independentes.
*/
char    *ft_strncpy_alloc(char *src, int n)
{
    int     i;
    char    *dest;

    dest = malloc((n + 1) * sizeof(char));
    if (!dest)
    {
        return(NULL);//Erro de alocação
    }
    
    //Copiar até 'n' caracteres
    i = 0;
    while (i < n && src[i])
    {
        dest[i] = src[i];
        i++;
    }
    //Preencher com '\0' se necessário
    while (i < n)
    {
        dest[i] = '\0';//Terminar string
        i++;
    }
    return(dest);
}

/*
    * ft_free_array
    * Libera toda a memória previamente alocada para o array de strings.
    * Implementada para garantir limpeza de memória em caso de erro ou
        ao final da execução.
*/
void    ft_free_array(char **array)
{
    int i;
    
    i = 0;
    while (array[i])
    {
        free(array[i]);//Liberar string individual
        i++;
    }
    free(array);//libera o array de ponteiros
}

/*
    * ft_fill_array
    * Percorre a string 'str' e preenche o array com substrings extraídas
        entre os separadores.
    * Utiliza 'ft_strncpy_alloc' para alocar cada palavra individualmente.
    * Essencial para montar o retorno final de 'ft_split'.
*/
int ft_fill_array(char **array, char *str, char *charset)
{
    int i;
    int start;
    int index_array;

    i = 0;
    index_array = 0;
    while(str[i])
    {
        //Pular separadores
        while(str[i] && ft_is_separator(charset, str[i]))
        {
            i++;
        }
        
        //Encontrou início de palavra
        if(str[i])
        {
            start = i;
            //Avançar até o fim da palavra
            while(str[i] && !ft_is_separator(charset, str[i]))
            {
                i++;
            }
        
            array[index_array] = ft_strncpy_alloc(&str[start], i - start);
            if(!array[index_array])
            {
                return(-1);//Erro de alocar
            }
            index_array++;
        }
    }
    array[index_array] = NULL;//Fim do array
    return(0);
}

/*
    * ft_split
    * Divide a string 'str' em substrings, separadas por qualquer caractere 
        presente em 'charset'.
    * Retorna um array de ponteiros para essas substrings, finalizado com NULL.
    * Cadeias vazias não são incluídas.
    * Parâmetros:
        - str: A string original que será dividida. Não é modificada.
        - charset: Conjunto de caracteres que serão usados como separadores entre 
            palavras.
    * Retorno:
        - Um array de strings contendo as palavras separadas.
        - NULL em caso de erro de alocação ou entrada inválida.
    * Funções auxiliares utilizadas:
        - ft_is_separator: verifica se um caractere é separador
        - ft_count_word: calcula quantas palavras serão extraídas
        - ft_strncpy_alloc: aloca e copia cada substring encontrada
        - ft_fill_array: extrai e preenche o array com as palavras
        - ft_free_array: usada para liberar memória em caso de falha
    * Implementada para trabalhar com qualquer conjunto de separadores, 
        permitindo divisão flexível de textos.
*/
char    **ft_split(char *str, char *charset)
{
    int     count_word;
    char    **array;

    if(!str || !charset)
    {
        return(NULL);//Entradas inválidas
    }
    count_word = ft_count_word(str, charset);
    array = malloc((count_word + 1) * sizeof(char *));
    if(!array)
    {
        ft_free_array(array);
        return(NULL);// Falha de alocação
    }


    if(ft_fill_array(array, str, charset) == -1)
    {
        ft_free_array(array);//Limpeza em caso de erro
        return(NULL);
    }
    return(array);//Retornar array com substrings
}

/*
    //Main para testar
    #include <stdio.h>
    int main(void)
    {
        char    **array;
        int     i;
        char    *str = "eu que";
        char    *charset = "am";
        
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
*/