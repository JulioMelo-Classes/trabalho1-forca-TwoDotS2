#include "../include/Forca.hpp"
// Bibliotecas para o transform
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

//Bibliotecas para o sorteio
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand

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
    std::string palavra;
    std::string frequencia_string;
    // Contador de linhas do arquivo
    int i = 1;

    while (fin >> palavra >> frequencia_string)
    {
        // Se a palavra não estiver entre [A-Z], ou não for ' ' ou
        // '-'. é enviada uma mensagem de erro
        for (char &ch : palavra)
        {
            if ((ch < 'A' || ch > 'Z') && (ch < 'a' || ch > 'z') && ch != ' ' && ch != '-')
            {
                fin.close();
                return std::pair<bool, std::string>(false, "Caractere inválido localizado na palavra :" + palavra +
                                                               " (linha " + std::to_string(i) + ")");
            }
        }
        // Para cada caractere da frequencia, se ela não estiver entre [0-9], é enviada uma mensagem de erro
        for (char &ch : frequencia_string)
        {
            if (ch < '0' || ch > '9')
            {
                fin.close();
                return std::pair<bool, std::string>(false, "Frequência não é um número inteiro positivo na palavra :" +
                                                               palavra + " (linha " + std::to_string(i) + ")");
            }
        }

        // Utilizando stoi() para transformar uma string em um inteiro
        int frequencia = stoi(frequencia_string);

        // Se a palavra tem 4 ou menos caracteres é enviada uma mensagem de erro
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

    // Abrindo arquivo de scores
    fin.open(m_arquivo_scores);
    // Verificar se conseguimos abrir o arquivo
    if (!fin.is_open())
    {
        // Disparando mensagem de erro caso não consiga abrir o arquivo de scores
        return std::pair<bool, std::string>(false, "Nenhum arquivo de scores foi encontrado em: " + m_arquivo_scores);
    }

    // resetando o contador
    i = 1;
    // Lendo as linhas do arquivo
    std::string line;
    while (std::getline(fin, line))
    {
        int semis = 0;
        for (auto &ch : line)
        {
            if (ch == ';')
            {
                semis++;
            }
        }

        if (semis != 3)
        {
            return std::pair<bool, std::string>(false, "Presença de " + std::to_string(semis) + " ';' na linha " +
                                                           std::to_string(i) + " do arquivo de scores [Esperado: 3]");
        }

        std::istringstream linha(line);

        std::string nivel;
        std::getline(linha, nivel, ';');
        if (nivel.size() == 0)
        {
            return std::pair<bool, std::string>(false, "Campo Nível de dificuldade vazio no arquivo de scores (linha " +
                                                           std::to_string(i) + ")");
        }

        std::string nome;
        std::getline(linha, nome, ';');
        if (nome.size() == 0)
        {
            return std::pair<bool, std::string>(false, "Campo Nome vazio no arquivo de scores (linha :" +
                                                           std::to_string(i) + ")");
        }

        std::string palavras_acertadas;
        std::getline(linha, palavras_acertadas, ';');

        std::string score_s;
        std::getline(linha, score_s);
        if (nome.size() == 0)
        {
            return std::pair<bool, std::string>(false, "Campo Score vazio no arquivo de scores (linha :" +
                                                           std::to_string(i) + ")");
        }

        // try
        // {
        //     int score = stoi(score_s);
        //     if (std::to_string(score) != score_s)
        //     {
        //         return std::pair<bool, std::string>(false, "Campo Score inválido no arquivo de scores (linha " +
        //                                                        std::to_string(i) + ")");
        //     }
        // }
        // catch (const std::exception &e)
        // {
        //     return std::pair<bool, std::string>(false, "Campo Score inválido no arquivo de scores (linha " +
        //                                                    std::to_string(i) + ")");
        // }

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

    fin.close();

    calcular_frequencia_media();
}

/**
 * Calcula através de média aritimética a média de frequência das
 * palavras do banco
 *
 * @param palavras
 * @return int
 */

void Forca::calcular_frequencia_media()
{
    int frequencia = 0;
    int media = 0;

    for (int i = 0; i < (int)m_palavras.size(); i++)
    {
        frequencia += m_palavras[i].second; //<! O valor da frequência da palavra[i] fica
                                            // armazenado na segunda parte do std::pair
    }

    media = frequencia / ((int)m_palavras.size()); //<! Média aritimética de inteiros, já que, nesse
                                                   // caso, não existe frequência com ponto flutuante
                                                   
    m_frequencia_media = media;
}

int myrandom (int i) { return std::rand() % i; }

void Forca::sortear_palavras()
{
    int qtd_filtradas; //<! Armazenar o total de palavras a serem filtradas

    // Aleatoriedade de 2.2, itens a,b,c, subitem i.
    //   'Insira na base Palavras do Jogo N palavras aleatórias'
    
    
    //Faz o sorteio linear (aleatoriedade somente por execução com main ativo)
    //std::random_shuffle(m_palavras.begin(), m_palavras.end());

    std::srand ( unsigned ( std::time(0) ) );
    std::random_shuffle(m_palavras.begin(), m_palavras.end(), myrandom);
    // Estudar: http://www.cplusplus.com/reference/algorithm/random_shuffle/

    //<! divisão dos filtros por dificuldade
    if (m_dificuldade == Forca::FACIL)
    {
        qtd_filtradas = 10;
        inserir_filtradas_facil(qtd_filtradas);
    }
    else if (m_dificuldade == Forca::MEDIO)
    {
        qtd_filtradas = 20;
        inserir_filtradas_medio(qtd_filtradas);
    }
    else if (m_dificuldade == Forca::DIFICIL)
    {
        qtd_filtradas = 30;
        inserir_filtradas_dificil(qtd_filtradas);
    }
}

/**
 * O objetivo dessa função é tornar mais legível a função filtrar_palavras_por_dificuldade.
 * 'inserir_filtradas_facil' serve para salvar as palavras da base de acordo com a condição 'Fácil'
 * @param palavras
 * @param m_palavras_do_jogo é o vetor que ira receber as palavras para o jogo
 * @param frequencia_media
 * @param qtd_filtradas
 */
void Forca::inserir_filtradas_facil(int qtd_filtradas)
{
    std::vector<std::string>::iterator it;
    for (int i = 0; i < (int)m_palavras.size(); i++)
    {
        // Insira na base 10 palavras aleatórias diferentes cuja frequência seja maior
        // do que a frequência média.
        if (m_palavras[i].second > m_frequencia_media)
        {
            it = std::find(m_palavras_do_jogo.begin(), m_palavras_do_jogo.end(), m_palavras[i].first);


           /** Pesquisar: it - m_palavras_do_jogo.begin() > 0
            *  https://www.geeksforgeeks.org/std-find-in-cpp/
            */ 
            if ((int)m_palavras_do_jogo.size() == 0 || it - m_palavras_do_jogo.begin() > 0)
            {
                m_palavras_do_jogo.push_back(m_palavras[i].first);
            }
        }

        if ((int)m_palavras_do_jogo.size() == qtd_filtradas)
            break;
    }
}

void Forca::inserir_filtradas_medio(int qtd_filtradas)
{
    std::vector<std::string>::iterator it;
    // For para percorrer a base
    for (int i = 0; i < (int)m_palavras.size(); i++)
    {
        it = std::find(m_palavras_do_jogo.begin(), m_palavras_do_jogo.end(), m_palavras[i].first);

        // 2.2 b) ii. '1/3 dessas palavras deve ser de palavras com frequência menor do que a média'
        // Buscando de palavra em palavra da base, verifica se as palavras do jogo atual já são 1/3 (6)
        // do total e aplica a condição de ser menor do que a média
        if ((int)m_palavras_do_jogo.size() != (int)(qtd_filtradas / 3))
        {
            if (m_palavras[i].second < m_frequencia_media)
            {
                //<! Caso std::find retorne o iterador do fim, significa que não há ocorrência.
                //<! Caso contrário, a palavra já existe entre as palavras do jogo
                if ((int)m_palavras_do_jogo.size() == 0 || it - m_palavras_do_jogo.begin() > 0)
                {
                    m_palavras_do_jogo.push_back(m_palavras[i].first);
                }
            }
        }
        else
            break;
        // Assim que 1/3 das palavras do jogo já tem frequência menor que a média, sai do laço
        // e preenche com a condição de ser maior que a frequência média
    }

    // For para percorrer a base desde o ínico, já que existe a possibilidade da condição acima só ocorrer
    // no fim da base
    for (int i = 0; i < (int)m_palavras.size(); i++)
    {
        it = std::find(m_palavras_do_jogo.begin(), m_palavras_do_jogo.end(), m_palavras[i].first);
        if (m_palavras[i].second > m_frequencia_media)
        {
            //<! Caso std::find retorne o iterador do fim, significa que não há ocorrência.
            //<! Caso contrário, a palavra já existe entre as palavras do jogo
            if ((int)m_palavras_do_jogo.size() == 0 || it - m_palavras_do_jogo.begin() > 0)
            {
                m_palavras_do_jogo.push_back(m_palavras[i].first);
            }
        }

        if ((int)m_palavras_do_jogo.size() == qtd_filtradas)
            break;
    }
}

void Forca::inserir_filtradas_dificil(int qtd_filtradas)
{
    std::vector<std::string>::iterator it;
    for (int i = 0; i < (int)m_palavras.size(); i++)
    {
        it = std::find(m_palavras_do_jogo.begin(), m_palavras_do_jogo.end(), m_palavras[i].first);
        // 2.2 c) ii. '3/4 dessas palavras deve ser de palavras com frequência menor do que a média'
        // Buscando de palavra em palavra da base, verifica se as palavras do jogo atual já são 3/4 (22)
        // do total e aplica a condição de ser menor do que a média
        if ((int)m_palavras_do_jogo.size() <= (int)(qtd_filtradas * 3 / 4))
        {
            if (m_palavras[i].second < m_frequencia_media)
            {
                if ((int)m_palavras_do_jogo.size() == 0 || it - m_palavras_do_jogo.begin() > 0)
                {
                    m_palavras_do_jogo.push_back(m_palavras[i].first);
                }
            }
        }
        else
            break;
    }

    for (int i = 0; i < (int)m_palavras.size(); i++)
    {
        it = std::find(m_palavras_do_jogo.begin(), m_palavras_do_jogo.end(), m_palavras[i].first);
        if (m_palavras[i].second > m_frequencia_media)
        {
            //<! Caso std::find retorne o iterador do fim, significa que não há ocorrência
            if (((int)m_palavras_do_jogo.size() == 0 || it - m_palavras_do_jogo.begin() > 0) && (int)m_palavras_do_jogo.size() != qtd_filtradas)
            {
                m_palavras_do_jogo.push_back(m_palavras[i].first);
            }
            else if ((int)m_palavras_do_jogo.size() == qtd_filtradas)
                break;
        }
    }
}

/////////////////////////////////////////////////////////////////////////
/////////// Menus
//////////////////////////////////////////////

/* void Forca::menu_handler(int opcao){
    std::string ultimo_menu, atual_menu = "info";
    if(atual_menu == "info"){
        switch(print_menu_informacoes()){
            case 1: int i = print_menu_dificuldades();
                    break;

            case 2: print_scores_registrados();
                    break;

            case 3: break;
        }
    }

}
*/

int Forca::print_menu_informacoes()
{
    int escolha = 0;
    std::cout << "Bem vindo ao Jogo Forca! Por favor escolha uma das opções" << std::endl;
    std::cout << "1 - Iniciar Jogo" << std::endl;
    std::cout << "2 - Ver scores anteriores" << std::endl;
    std::cout << "3 - Sair do Jogo" << std::endl;
    std::cout << "Sua escolha: "; 
    std:: cin >> escolha;
    return escolha;
}

int Forca::print_menu_dificuldades()
{
    int escolha = 0;
    std::cout << "Vamos iniciar o jogo! Por favor escolha o nível de dificuldade" << std::endl;
    std::cout << "1 - Fácil" << std::endl;
    std::cout << "2 - Médio" << std::endl;
    std::cout << "3 - Difícil" << std::endl;
    std::cout << "Sua escolha: "; 
    std:: cin >> escolha;
    return escolha;


}

void Forca::print_scores_registrados()
{

}

void Forca::print_forca_ui()
{
    std::cout << "Iniciando o Jogo no nível Médio, será que você conhece essa palavra?" << std::endl;
    //
}

void Forca::print_filtradas()
{
    for (int i = 0; i < (int)m_palavras_do_jogo.size(); i++)
        std::cout << i << ": " << m_palavras_do_jogo[i] << std::endl;
}