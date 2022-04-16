#include "Forca.hpp"
// Bibliotecas para o transform
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Biblioteca de exceções
#include <stdexcept>

// Construtor
// O valor das strings serão os caminhos para chegar no arquivo
Forca::Forca(std::string __palavras, std::string __scores)
{
    m_arquivo_palavras = __palavras;
    m_arquivo_scores = __scores;
};

std::pair<bool, std::string> Forca::eh_valido()
{
    // Procurar o arquivo para saber se ele existe
    // Declarando variável para leitura de arquivos
    std::ifstream fin;
    // Passando o caminho do arquivo que vamos abrir
    fin.open(m_arquivo_palavras);
    // Verificar se conseguimos abrir o arquivo
    if (!fin.is_open())
    {
        // Disparando mensagem de erro caso não consiga abrir o arquivo de palavras
        return std::pair<bool, std::string>(false,
                                            "Nenhum arquivo de palavras foi encontrado em: " + m_arquivo_palavras);
    }
    // Lendo arquivo
    std::string line;
    std::string palavra;
    std::string frequencia_string;
    // Contador de linhas do arquivo
    int i;

    while (fin >> palavra >> frequencia_string)
    {
        // Se a palavra em caixa alta não estiver entre [A-Z], ou não for ' ' ou
        // '-'. é disparada uma exceção Para cada caractere da palavra
        for (char &ch : palavra)
        {
            if ((ch < 'A' || ch > 'Z') && (ch < 'a' || ch > 'z') && ch != ' ' && ch != '-')
            {
                fin.close();
                return std::pair<bool, std::string>(false, "Caractere inválido localizado na palavra " + palavra +
                                                               "(linha" + std::to_string(i) + ")");
            }
        }
        // Para cada caractere da frequencia, se ela não estiver entre [0-9], é
        // disparada uma exceção
        for (char &ch : frequencia_string)
        {
            if (ch < '0' || ch > '9')
            {
                fin.close();
                return std::pair<bool, std::string>(false, "Frequência não é um número inteiro positivo na palavra " +
                                                               palavra + "linha" + std::to_string(i) + ")");
            }
        }

        // Utilizando stoi() para transformar uma string em um inteiro
        int frequencia = stoi(frequencia_string);

        // Se a palavra tem 4 ou menos caracteres é disparada uma exceção
        if (palavra.size() <= 4)
        {
            fin.close();
            return std::pair<bool, std::string>(false, "Palavra com tamanho menor ou igual a 4: " + palavra +
                                                           " (linha " + std::to_string(i) + ")");
        }

        // Passando para próxima linha
        i++;
    }

    fin.close();
    return std::pair<bool, std::string>(true, "");
}

void Forca::carregar_arquivos()
{
    std::ifstream fin;
    fin.open(m_arquivo_palavras);

    std::string line;
    std::string palavra;
    int frequencia;

    while (fin >> palavra >> frequencia)
    {
        std::string upper = palavra;
        // transformando a palavra para caixa alta e salvando em "upper"
        transform(palavra.begin(), palavra.end(), upper.begin(), ::toupper);

        // adicionando o par de palavra e frequencia no fim do vetor m_palavras
        m_palavras.push_back(std::pair<std::string, int>(upper, frequencia));
    }

    for (auto &par : m_palavras)
    {
        std::cout << par.first << " (" << par.second << ")" << std::endl;
    }

    fin.close();
}

/**
 * @brief Calcula através de média aritimética a média de frequência das
 * palavras do banco
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
        frequencia += palavras[i].second; //<! O valor da frequência da palavra[i] fica
                                          // armazenado na segunda parte do std::pair
    }

    media = frequencia / ((int)palavras.size()); //<! Média aritimética de inteiros, já que, nesse
                                                 // caso, não existe frequência com ponto flutuante

    return frequencia;
}

std::vector<std::string> filtrar_palavras_por_dificuldade(Forca::Dificuldade dificuldade, std::string arquivo_palavras,
                                                          int frequencia_media)
{
    std::vector<std::string> filtradas; //<! Vetor que vai receber as palavras diferentes, tratadas
    // baseadas na dificuldade
    int qtd_filtradas; //<! Armazenar o total de palavras a serem filtradas e
                       // adicionadas ao vetor

    /** Sempre será suposto que haverá o suficiente de palavras para serem
     * filtrads da base de dados ('./palavras.txt') ou pelo menos uma, para não
     * quebrar o resto da aplicação.
     *
     * Obs.: Inserir palavra a força, caso não exista? [péssimo]
     */

    //<! divisão dos filtros por dificuldade
    if (dificuldade == Forca::FACIL)
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