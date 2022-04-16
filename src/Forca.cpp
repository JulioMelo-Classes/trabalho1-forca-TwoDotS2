#include "Forca.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

std::pair<bool, std::string> eh_valido()
{
    return std::pair<bool, std::string>{};
}

/**
 * @brief Calcula através de média aritimética a média de frequência das palavras do banco
 *
 * @param palavras
 * @return int
 */

int calcular_frequencia_media(std::vector<std::pair<std::string, int>> palavras)
{
    int frequencia = 0;
    int media = 0;

    
    for (int i = 0; i < (int)palavras.size(); i++)
    {
        frequencia += palavras[i].second; //<! O valor da frequência da palavra[i] fica armazenado na segunda parte do std::pair
    }

    media = frequencia / ((int)palavras.size()); //<! Média aritimética de inteiros, já que, nesse caso, não existe frequência com ponto flutuante

    return frequencia;
}

std::vector<std::string> filtrar_palavras_por_dificuldade(Forca::Dificuldade dificuldade, std::string arquivo_palavras, int frequencia_media)
{
    std::vector<std::string> filtradas; //<! Vetor que vai receber as palavras diferentes, tratadas baseadas na dificuldade 
    int qtd_filtradas; //<! Armazenar o total de palavras a serem filtradas e adicionadas ao vetor

    /** Sempre será suposto que haverá o suficiente de palavras para serem
     * filtrads da base de dados ('./palavras.txt') ou pelo menos uma, para não quebrar
     * o resto da aplicação.
     * 
     * Obs.: Inserir palavra a força, caso não exista? [péssimo]
     */

    //<! divisão dos filtros por dificuldade
    if(dificuldade == Forca::FACIL)
    {
        qtd_filtradas = 10;

    } 
    else if (dificuldade == Forca::MEDIO)
    {
        qtd_filtradas = 20;
    } 
    else if (dificuldade == Forca::DIFICIL)
    {
        qtd_filtradas = 30;
    }
    

    return filtradas;
}