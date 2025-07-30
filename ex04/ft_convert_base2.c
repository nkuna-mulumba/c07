/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucongol <jucongol@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-30 18:53:16 by jucongol          #+#    #+#             */
/*   Updated: 2025-07-30 18:53:16 by jucongol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
    * Verifica se a string `base` representa uma base válida para conversão numérica.
    * Regras para validade:
        - Deve ter pelo menos dois caracteres.
        - Não pode conter espaços, sinais '+' ou '-', ou caracteres não imprimíveis.
        - Não pode ter caracteres repetidos.
    * Parâmetros:
        - base: string que representa os caracteres válidos da base.
    * Retorna 1 se a base for válida, ou 0 caso contrário.
*/
int    ft_is_valid_base(char *base)
{
    int i;
    int j;

    i = 0;
    if(!base || !base[i] || !base[i + 1])
    {
        return(0);
    }
    while(base[i])
    {
        if((base[i] >= 9 && base[i] <= 13) || base[i] == ' ' || base[i] == '+' || base[i] == '-')
        {
            return(0);
        }
        i++;
    }

    i = 0;
    while(base[i])
    {
        j = i + 1;
        while(base[j])
        {
            if(base[j] == base[i])
            {
                return(0);
            }
            j++;
        }
        i++;
    }
    return(1);
}

/*
    * Função auxiliar que busca o índice de um caractere dentro de uma string.
    * É usada principalmente para verificar se um caractere pertence à base fornecida
        e obter seu valor numérico correspondente para conversão.
    * Parâmetros:
        - str: string que representa os caracteres válidos da base
        - c: caractere a ser buscado dentro da string `str`
    * Retorna o índice de `c` em `str` se encontrado, ou -1 se `c` não pertence à base.
*/
int ft_get_index(char *str, char c)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] == c)
        {
            return(i);
        }
        i++;
    }
    return(-1);
}

/*
    * Função auxiliar que prepara a leitura de um número contido em uma string.
    * Ela ignora os espaços em branco no início da string e analisa os sinais '+' e '-',
        definindo corretamente o fator de sinal multiplicativo para o número.
    * Parâmetros:
        - str: string contendo o número a ser lido
        - sign: ponteiro para um inteiro que será preenchido com o sinal final (+1 ou -1)
    * Retorna o índice inicial da parte numérica da string, após espaços e sinais.
*/

int ft_prepare_nbr_start(char *str, int *sign)
{
    int i;

    i = 0;
    while((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
    {
        i++;
    }

    *sign = 1;
    while(str[i] == '+' || str[i] == '-')
    {
        if(str[i] == '-')
        {
            *sign *= -1;
        }
        i++;
    }
    return(i);
}
/*
    * Função auxiliar que converte uma string representando um número em uma base
        específica para seu valor equivalente em base decimal (int).
    * Essa função é usada como etapa inicial na conversão entre bases.
    * Ela processa a string `str`, que contém o número na base `base`, valida a base,
        ignora espaços e sinais, e transforma o número em um inteiro decimal.
    * Parâmetros:
        - str: string com o número na base original
        - base: string contendo os caracteres válidos da base (ex: "0123456789abcdef")
    * Retorna o valor inteiro correspondente à string `str`.
    * Se a base for inválida, retorna 0.
*/

int ft_atoi_base(char *str, char *base)
{
    int len_base;
    int i;
    int sign;
    int nbr;
    int dig;

    // Verificar se base fornecida é válida
    if(ft_is_valid_base(base) == 0)
    {
        return(0);
    }

    //Calcula comprimento da base
    len_base = 0;
    while(base[len_base])
    {
        len_base++;
    }

    //Preparar para começar leitura do número: ignora espaços, define sinal (+/-)
    i = ft_prepare_nbr_start(str, &sign);

    //Converte caractere por caractere para formar o número decimal
    nbr = 0;
    while(str[i] && ft_get_index(base, str[i]) != -1)
    {
        dig = ft_get_index(base, str[i]);//O valor numérico do caractere
        nbr = nbr * len_base + dig;//Atualiza o número acumulado
        i++;
    }
    return(sign * nbr);//Aplica o sinal e retorna o resultado final
}
