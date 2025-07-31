/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:17:14 by jucongol          #+#    #+#             */
/*   Updated: 2025/07/31 12:58:41 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int ft_is_valid_base(char *base);
int ft_atoi_base(char *str, char *base);

/*
   * Função auxiliar que calcula o tamanho (comprimento) de uma string.
   * Essa função percorre cada caractere da string até encontrar o caractere nulo '\0',
        contando quantos caracteres existem. Muito utilizada em outras 
        funções que lidam
        com manipulação de strings, inclusive nas conversões de base.
    * Parâmetro:
        - str: ponteiro para a string cujo tamanho será calculado.
    * Retorna o número de caracteres na string, excluindo o caractere nulo final.
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
    * Função auxiliar responsável por gerar a string final correspondente
        ao número em sua base destino (`base_to`).
    * Parametros:
        - tmp: o número já convertido para decimal (positivo)
        - base_to: a base destino (ex: binário, hexadecimal, etc.)
        - size: quantidade de dígitos necessários para representar tmp
        - sign: indica se o número original era negativo (0 ou 1)
    * A função aloca dinamicamente a string de saída, calcula os dígitos
        do número na nova base e os insere na posição correta.
    * Se o número era negativo, adiciona um '-' no início.
    * Retorna a string resultante ou NULL se falhar na alocação.
*/
char    *ft_convert_unsigned_to_base(unsigned int tmp, char *base_to, int size, int sign)
{
    unsigned    len_base;
    char        *res;

    //Calcula tamanho da base destino (quantidade de dígitos disponíveis)
    len_base = (unsigned)ft_strlen(base_to);

    //Aloca espaço para string resultado (+1 para '\0' e +sign se negativo)
    res = malloc(size + sign + 1);
    if(!res)
    {
        return(NULL);
    }
    res[size + sign] = '\0';//Finaliza a string com '\0'

    //Converte cada dígito de tmp para o correspondente na base destino
    while(size > 0)
    {
        res[size - 1 + sign] = base_to[tmp % len_base];//Insere dígito na posição
        tmp = tmp / len_base;//Reduz valor para próximo dígito
        size--;
    }

    //Se número original era negativo, adiciona sinal '-' no início
    if(sign == 1)
    {
        res[0] = '-';
    }
    return(res);
}

/*
    * Função auxiliar para converter um número inteiro em uma string
        representando esse número em uma base específica.
    * Essa função é usada como parte do processo de conversão de bases,
        transformando um valor decimal (`int nbr`) em uma string na base
        de destino (`base_to`), por exemplo: decimal → binário, hexadecimal, etc.
    * Parâmetros:
        - nbr: número inteiro a ser convertido
        - base_to: string contendo os caracteres válidos da base de destino
    * Retorna uma nova string representando o número `nbr` na base `base_to`.
    * Em caso de base inválida, retorna NULL.
*/

char    *ft_itoa_base(int nbr, char *base_to)
{
    unsigned int    len_base;
    int             sign;
    unsigned int    tmp;
    int             size;
    unsigned int    calc;

    //Verificar se a base destino é válida
    if(!ft_is_valid_base(base_to))
    {
        return(NULL);
    }

    //Obter comprimento da base destino (quantidade de dígitos possíveis)
    len_base = (unsigned int)ft_strlen(base_to);
    sign = 0;

    //Se número for negativo, marca o sinal e transforma em positivo
    if(nbr < 0)
    {
        sign = 1;
        tmp = (unsigned int)(-((long)nbr));//Lida com limites de int
    }
    else
    {
        tmp = (unsigned int)nbr;
    }

    //Calcula o número de dígitos necessários na base destino
    size = 1;
    calc = tmp;
    while(calc >= len_base)
    {
        calc = calc / len_base;
        size++;
    }
    //Chama função auxiliar para montar a string final
    return(ft_convert_unsigned_to_base(tmp, base_to, size, sign));
}

/*
    * Esta função tem como objetivo converter um número representado como string
        em uma determinada base (`base_from`) para outra base (`base_to`).
    * Parâmetros:
    * - nbr: string que representa o número na base de origem
      - base_from: string que define os caracteres válidos da base de origem
      - base_to: string que define os caracteres válidos da base de destino
    * A função valida as bases e o número, converte o número de `base_from` para
        decimal, e em seguida converte esse valor decimal para a `base_to`.
    * Retorna uma nova string com o número convertido para a base desejada.
    * Caso alguma das bases seja inválida ou ocorra erro, retorna NULL.
*/
char *ft_convert_base(char *nbr, char *base_from, char *base_to)
{
    int n;

    //Verificar se as bases fornecidas são válidas
    if(!ft_is_valid_base(base_from) || !ft_is_valid_base(base_to))
    {
        return(NULL);
    }

    //Converte a string 'nbr' da base 'base_from' para um inteiro decimal
    n = ft_atoi_base(nbr, base_from);

    //Converte o inteiro decimal 'n' para uma string na base 'base_to'
    return(ft_itoa_base(n , base_to));
}

/*
    #include <stdio.h>
    int main(void)
    {
        char    *nbr = "ab";
        char    *base_from = "0123456789abcdef";
        char    *base_to = "01";

        char    *res = ft_convert_base(nbr, base_from, base_to);
        if (res)
        {
            printf("Resultado da conversão: %s\n", res);
            free(res);
        }
        else
        {
            printf("Conversão falhou (base inválida ou erro).\n");
        }
        
        return 0;
    }
*/