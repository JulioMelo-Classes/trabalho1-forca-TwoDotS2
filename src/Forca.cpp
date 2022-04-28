/**
 * Tags:
 *      [NÃO FINALIZADO], [DEBUG], [TESTE]
 */

#include "../include/Forca.hpp"

// Construtor
// O valor das strings serão os caminhos para chegar no arquivo
Forca::Forca(std::string __palavras, std::string __scores)
{
    m_arquivo_palavras = __palavras;
    m_arquivo_scores = __scores;
    m_tentativas_restantes = 6; //<! Braços(2), pernas(2), tronco(1), cabeça (1) = 6 partes
    m_pontos = 0;
}

void Forca::set_dificuldade(Forca::Dificuldade d)
{
    m_dificuldade = d;
}

void Forca::set_palavra_atual(std::string p)
{
    m_palavra_atual = p;
    set_palavra_jogada();
}

void Forca::set_palavra_jogada()
{
    int ii = 0;
    while (ii < m_palavra_atual.length())
    {
        m_palavra_jogada.push_back('_');
        ++ii;
    }
}

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

    while (fin >> palavra)
    {
        // Se os caracteres da palavra não estiverem entre [A-Z], ou não forem ' ' ou
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

        // Utilizando stoi() para transformar uma string em um inteiro
        // int frequencia = stoi(frequencia_string);

        // Se a palavra tem 4 ou menos caracteres é enviada uma mensagem de erro
        if (palavra.size() <= 4)
        {
            fin.close();
            return std::pair<bool, std::string>(false, "Palavra com tamanho menor ou igual a 4: " + palavra +
                                                           " (linha " + std::to_string(i) + ")");
        }
        if (fin >> frequencia_string)
        {
            // Para cada caractere da frequencia, se ela não estiver entre [0-9], é enviada uma mensagem de erro
            for (char &ch : frequencia_string)
            {
                if (ch < '0' || ch > '9')
                {
                    fin.close();
                    return std::pair<bool, std::string>(false, "Frequência não é um número inteiro positivo na palavra: " +
                                                                   palavra + " (linha " + std::to_string(i) + ")");
                }
            }
        }
        else
        {
            fin.close();
            return std::pair<bool, std::string>(false, "Não existe frequência referente à palavra: " +
                                                           palavra + " (linha " + std::to_string(i) + ")");
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
        // contador de ponto e virgula
        int semis = 0;
        // char
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
            return std::pair<bool, std::string>(false, "Campo Nome vazio no arquivo de scores (linha " +
                                                           std::to_string(i) + ")");
        }

        std::string palavras_acertadas;
        std::getline(linha, palavras_acertadas, ';');

        std::string score_s;
        std::getline(linha, score_s);
        // ALTERAR SCORE
        if (score_s.size() == 0)
        {
            return std::pair<bool, std::string>(false, "Campo Score vazio no arquivo de scores (linha " +
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

// Imprimindo os scores formatados
void Forca::print_scores_registrados()
{
    struct Score
    {
        std::string nivel;
        std::string nome;
        std::vector<std::string> palavras;
        int score;
    };

    std::vector<Score> scores;

    std::string stringNivel = "Dificuldade";
    std::string stringNome = "Jogador";
    std::string stringPalavras = "Palavras";
    std::string stringPontos = "Pontos";

    int tamNivel = stringNivel.size();
    int tamNome = stringNome.size();
    int tamPalavras = stringPalavras.size();
    int tamPontos = stringPontos.size();

    std::ifstream fin;
    fin.open(m_arquivo_scores);

    std::string line;
    while (std::getline(fin, line))
    {
        std::istringstream linha(line);

        std::string nivel;
        std::getline(linha, nivel, ';');

        std::string nome;
        std::getline(linha, nome, ';');

        std::string palavras_acertadas;
        std::getline(linha, palavras_acertadas, ';');

        std::vector<std::string> palavras_separadas;

        std::istringstream palavras(palavras_acertadas);
        std::string palavra;
        while (std::getline(palavras, palavra, ','))
        {
            palavras_separadas.push_back(palavra);
            tamPalavras = std::max(tamPalavras, (int)palavra.size());
        }

        std::string score_s;
        std::getline(linha, score_s);
        int score = stoi(score_s);

        scores.push_back(Score{nivel, nome, palavras_separadas, score});

        tamNivel = std::max(tamNivel, (int)nivel.size());
        tamNome = std::max(tamNome, (int)nome.size());
        tamPontos = std::max(tamPontos, (int)score_s.size());
    }

    // Cabeçalho
    std::cout << std::left;
    std::cout.width(tamNivel + 1);
    std::cout << stringNivel + " ";
    std::cout << "|";
    std::cout << std::left;
    std::cout.width(tamNome + 2);
    std::cout << " " + stringNome + " ";
    std::cout << "|";
    std::cout << std::left;
    std::cout.width(tamPalavras + 2);
    std::cout << " " + stringPalavras + " ";
    std::cout << "|";
    std::cout << std::left;
    std::cout.width(tamPontos + 1);
    std::cout << " " + stringPontos;
    std::cout << std::endl;

    for (auto &score : scores)
    {
        if (score.palavras.size() == 0)
        {
            std::cout << std::left;
            std::cout.width(tamNivel + 1);
            std::cout << score.nivel + " ";
            std::cout << "|";
            std::cout << std::left;
            std::cout.width(tamNome + 2);
            std::cout << " " + score.nome + " ";
            std::cout << "|";
            std::cout << std::left;
            std::cout.width(tamPalavras + 2);
            std::cout << " <nenhuma> ";
            std::cout << "|";
            std::cout << std::left;
            std::cout.width(tamPontos + 1);
            std::cout << " " + std::to_string(score.score);
            std::cout << std::endl;
        }
        else
        {
            std::cout << std::left;
            std::cout.width(tamNivel + 1);
            std::cout << score.nivel + " ";
            std::cout << "|";
            std::cout << std::left;
            std::cout.width(tamNome + 2);
            std::cout << " " + score.nome + " ";
            std::cout << "|";
            std::cout << std::left;
            std::cout.width(tamPalavras + 2);
            std::cout << " " + score.palavras[0] + " ";
            std::cout << "|";
            std::cout << std::left;
            std::cout.width(tamPontos + 1);
            std::cout << " " + std::to_string(score.score);
            std::cout << std::endl;

            for (int i = 1; i < score.palavras.size(); i++)
            {
                std::cout << std::left;
                std::cout.width(tamNivel + 1);
                std::cout << " ";
                std::cout << "|";
                std::cout << std::left;
                std::cout.width(tamNome + 2);
                std::cout << " ";
                std::cout << "|";
                std::cout << std::left;
                std::cout.width(tamPalavras + 2);
                std::cout << " " + score.palavras[i] + " ";
                std::cout << "|";
                std::cout << std::left;
                std::cout.width(tamPontos + 1);
                std::cout << " ";
                std::cout << std::endl;
            }
        }

        for (int i = 0; i < tamNivel + 1; i++)
        {
            std::cout << "-";
        }
        std::cout << "+";
        for (int i = 0; i < tamNome + 2; i++)
        {
            std::cout << "-";
        }
        std::cout << "+";
        for (int i = 0; i < tamPalavras + 2; i++)
        {
            std::cout << "-";
        }
        std::cout << "+";
        for (int i = 0; i < tamPontos + 1; i++)
        {
            std::cout << "-";
        }
        std::cout << std::endl;
    }

    fin.close();
}

void Forca::carregar_arquivos()
{
    std::ifstream fin;
    fin.open(m_arquivo_palavras);

    // std::string line;
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

int myrandom(int i) { return std::rand() % i; }

void Forca::sortear_palavras()
{
    int qtd_filtradas; //<! Armazenar o total de palavras a serem filtradas

    // Aleatoriedade de 2.2, itens a,b,c, subitem i.
    //   'Insira na base Palavras do Jogo N palavras aleatórias'

    // Faz o sorteio linear (aleatoriedade somente por execução com main ativo)
    // std::random_shuffle(m_palavras.begin(), m_palavras.end());

    std::srand(unsigned(std::time(0)));
    std::random_shuffle(m_palavras.begin(), m_palavras.end(), myrandom);

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

int Forca::print_menu_informacoes()
{
    int escolha = 0;
    std::cout << "Bem vindo ao Jogo Forca! Por favor escolha uma das opções" << std::endl;
    std::cout << "1 - Iniciar Jogo" << std::endl;
    std::cout << "2 - Ver scores anteriores" << std::endl;
    std::cout << "3 - Sair do Jogo" << std::endl;
    std::cout << "Sua escolha: ";
    std::cin >> escolha;

    std::cout << std::endl
              << "------------------------------------------------------------------------------------------";
    std::cout << std::endl
              << std::endl;

    return escolha;
}

Forca::Dificuldade Forca::print_menu_dificuldades()
{
    int escolha = 0;
    Forca::Dificuldade d;

    std::cout << "Vamos iniciar o jogo! Por favor escolha o nível de dificuldade" << std::endl;
    std::cout << "1 - Fácil" << std::endl;
    std::cout << "2 - Médio" << std::endl;
    std::cout << "3 - Difícil" << std::endl;
    std::cout << "Sua escolha: ";
    std::cin >> escolha;

    std::cout << std::endl
              << "------------------------------------------------------------------------------------------";
    std::cout << std::endl
              << std::endl;

    if (escolha == 1)
        d = Dificuldade::FACIL;
    if (escolha == 2)
        d = Dificuldade::MEDIO;
    if (escolha == 3)
        d = Dificuldade::DIFICIL;

    return d;
}

void Forca::proxima_palavra()
{
    std::vector<std::string> dificuldades = {"Fácil", "Médio", "Difícil"};

    std::cout << "Iniciando o Jogo no nível " << dificuldades[(int)m_dificuldade]
              << ", será que você conhece essa palavra?" << std::endl;

    //  Como m_palavras_do_jogo já está ordenado aleatoriamente, é possível chamar uma posição a fixa,
    //  no caso, a última posição. Utilizando isso é possível usar std::vector.pop_back() no fim
    //  da rodada.

    set_palavra_atual(m_palavras_do_jogo[m_palavras_do_jogo.size() - 1]);
}

std::pair<bool, bool> Forca::palpite(std::string palpite)
{
    std::pair<bool, bool> tipo_palpite;
    std::vector<char>::iterator it_letras_palpitadas;

    //<! Palpite existe na palavra
    if (m_palavra_atual.find(palpite[0]) != std::string::npos)
        tipo_palpite.first = true;
    else
        tipo_palpite.first = false;

    //<! Palpite é ou não é novo

    it_letras_palpitadas = std::find(m_letras_palpitadas.begin(), m_letras_palpitadas.end(), palpite[0]);
    if (it_letras_palpitadas == m_letras_palpitadas.end())
    {
        tipo_palpite.second = true;
        m_letras_palpitadas.push_back(palpite[0]);
    } else
        tipo_palpite.second = false;

    return tipo_palpite;
}

/**
 * Serve para fornecer uma dica ao jogador de acordo com a dificuldade do jogo.
 */

void Forca::dica_palavra_jogada()
{
    std::srand(unsigned(std::time(0)));
    std::vector<int> last_indexes;
    std::vector<int>::iterator it;
    int random;

    // Preciso garantir que vai acontecer
    if (m_dificuldade == Forca::FACIL)
    {
        int num = std::max(1, (int)m_palavra_atual.size() / 5), count = 0;
        while (count < num)
        {

            random = rand() % ((int)m_palavra_atual.size() - 1);
            it = std::find(last_indexes.begin(), last_indexes.end(), random);

            // Se o índice não foi sorteado ainda
            if (it == last_indexes.end())
            {
                // Se o caracter no índice não sorteado não é uma vogal
                if ((m_palavra_atual[random] != 'A') && (m_palavra_atual[random] != 'E') &&
                    (m_palavra_atual[random] != 'I') && (m_palavra_atual[random] != 'O') && (m_palavra_atual[random] != 'U'))
                {
                    m_palavra_jogada[random] = m_palavra_atual[random];
                    count++;
                }

                last_indexes.push_back(random);
            }
        }
    }

    if (m_dificuldade == Forca::MEDIO)
    {
        while (true)
        {
            random = rand() % ((int)m_palavra_atual.size() - 1);

            if ((m_palavra_atual[random] == 'A') || (m_palavra_atual[random] == 'E') ||
                (m_palavra_atual[random] == 'I') || (m_palavra_atual[random] == 'O') ||
                (m_palavra_atual[random] == 'U'))
            {
                m_palavra_jogada[random] = m_palavra_atual[random];
                break;
            }
        }
    }
}

//Retorna se o palpite é válido
bool Forca::validar_palpite(std::string palpite){
    
    if(palpite.size() != 1) return false;
    if( (palpite[0] < 'A' || palpite[0] > 'Z') ) return false;

    return true;
}

//[NÃO FINALIZADO]
//<! Referência: https://github.com/AngularsCoding/Hangman/blob/main/Hangman.cpp
void Forca::print_hangman(){
    std::cout << std::endl;
    std::cout << "Resta(m) " << m_tentativas_restantes << " tentativa(s)" << std::endl; 
    std::cout << std::endl;
	std::cout << "  -----" << std::endl;
	std::cout << "  |   |" << std::endl; 
	std::cout << "  |";    if(m_tentativas_restantes<=5) std::cout<<"   O    "; std::cout<<std::endl;
	std::cout << "  |";    if(m_tentativas_restantes<=2) std::cout<<"  /|\\   "; std::cout<<std::endl;
	std::cout << "  |";    if(m_tentativas_restantes<=1) std::cout<<"  / \\    "; std::cout<<std::endl;
	std::cout << "  |"   << std::endl; 
	std::cout << "__|__" << std::endl << std::endl;;
}

std::string Forca::print_forca_ui()
{
    std::cout << "------------------------------------------------------------------------------------------" << std::endl;
    //[TESTE]
    //std::cout << "(Palavra atual: " << m_palavra_atual << " )" << std::endl;
    std::cout << "Lista de Palpites: " << std::endl;
    std::cout << "[ ";
    for (int ii = 0; ii < (int)m_letras_palpitadas.size(); ++ii)
    {
        if (ii == (int)m_letras_palpitadas.size())
            std::cout << m_arquivo_palavras[ii];
        else
            std::cout << m_arquivo_palavras[ii] << ", ";
    }
    std::cout << " ]" << std::endl << std::endl;

    std::string palpite;
    
    print_hangman();

    for (int ii = 0; ii < (int)m_palavra_jogada.size(); ++ii)
    {
        if (ii != (int)m_palavra_jogada.size() - 1)
            std::cout << m_palavra_jogada[ii] << " ";
        else
            std::cout << m_palavra_jogada[ii];
    }
    std::cout << std::endl;

    std::cout << "Pontos: " << m_pontos << std::endl;
    std::cout << "Palpite: ";
    
    std::cin >> palpite;

    std::cout << std::endl;

    while(!validar_palpite(palpite)){
        std::cout << "Palpite Inválido. Digite novo palpite:" << std::endl;
        std::cout << "Palpite: ";
        std::cin >> palpite; 
    }

    return palpite;
}

std::string Forca::print_forca_ui(std::pair<bool, bool> palpite, std::string ultimo_palpite)
{
    std::cout << "------------------------------------------------------------------------------------------" << std::endl;
    //[TESTE]
    //std::cout << "(Palavra atual: " << m_palavra_atual << " )" << std::endl;
    std::cout << "Lista de Palpites: " << std::endl;

    std::cout << "[ ";
    for (int ii = 0; ii < (int)m_letras_palpitadas.size(); ++ii)
    {
        if (ii == (int)m_letras_palpitadas.size())
            std::cout << m_letras_palpitadas[ii];
        else
            std::cout << m_letras_palpitadas[ii] << ", ";
    }
    std::cout << " ]" << std::endl << std::endl;

    if (palpite.first == true)
    {
        if (palpite.second == true)
        {
            //{T,T}: o palpite pertence à palavra e é um palpite novo
            std::cout << "Muito bem! A palavra contém a letra " << ultimo_palpite << "!" << std::endl;
        }
        else
        {
            //{T,F}: o palpite pertence à palavra, mas não é um palpite novo palpite
            std::cout << "Você já tentou com a letra " << ultimo_palpite << "!" << std::endl;
        }
    }
    else
    {
        if (palpite.second == true)
        {
            //{F,T} não pertence à palavra e é novo.
            std::cout << "Meh, não achei a letra " << ultimo_palpite << "! :<" << std::endl;
        }
        else
        {
            //{F,F} não pertence à palavra e não é novo.
            std::cout << "Você já tentou com a letra " << ultimo_palpite << "!" << std::endl;
        }
    }

    print_hangman();


    for (int ii = 0; ii < (int)m_palavra_jogada.size(); ++ii)
    {
        if (ii != (int)m_palavra_jogada.size() - 1)
            std::cout << m_palavra_jogada[ii] << " ";
        else
            std::cout << m_palavra_jogada[ii];
    }
    std::cout << std::endl;

    std::string str;
    std::cout << "Pontos: " << m_pontos << std::endl;
    std::cout << "Palpite: ";
    std::cin >> str;

    std::cout << std::endl;

    while(!validar_palpite(str)){
        std::cout << "Palpite Inválido. Digite novo palpite:" << std::endl;
        std::cout << "Palpite: ";
        std::cin >> str; 
    }

    return str;
}

void Forca::atualizar_tentativas(std::pair<bool, bool> tipo_palpite)
{
    // Há redução de palpites quando o mesmo não fizer parte da palavra
    if (!tipo_palpite.first)
    {
        --m_tentativas_restantes;
    }
}

void Forca::atualizar_pontos(std::pair<bool, bool> tipo_palpite, std::string ultimo_palpite)
{
    std::string str = "_";
    // {T,T} se o palpite pertence à palavra e é um palpite novo,
    if (tipo_palpite.first && tipo_palpite.second)
    {
        for (int ii = 0; ii < m_palavra_atual.size(); ++ii)
        {
            // É necessário comparar (m_palavra_jogada[ii] == "_"), umas vez que existe a 'dica'
            // no início
            if (m_palavra_atual[ii] == ultimo_palpite[0] && m_palavra_jogada[ii] == str[0])
            {

                m_palavra_jogada[ii] = ultimo_palpite[0];

                ++m_pontos;
                
                // A última letra vale 2 pontos
                if (ii == m_palavra_atual.size() - 1)
                    m_pontos += 2;
            }
        }
    }

    // {T,F} no caso do palpite pertencer à palavra, mas não é novo.
    // Caso desnecessário pelo item 4.e)

    // {F,T} caso não pertença e é novo.
    if (!tipo_palpite.first && tipo_palpite.second)
        --m_pontos;

    // {F,F} no caso do palpite não pertencer à palavra e não é novo.
    if (!tipo_palpite.first && !tipo_palpite.second)
        --m_pontos;
}

void Forca::print_game_over()
{
    std::cout << "Pontos: " << m_pontos << std::endl;
    std::cout << "O jogo acabou, a palavra era " << m_palavra_atual << "!" << std::endl;
}

bool Forca::print_continuar_jogando()
{
    std::string op;
    bool b = true;
    
    std::cout << "------------------------------------------------------------------------------------------" << std::endl;

    std::cout << "Você acertou! Parabéns! A palavra era " << m_palavra_atual << "!" << std::endl
              << std::endl;

    std::cout << "------------------------------------------------------------------------------------------" << std::endl << std::endl;
   
    //Salva palavra acertada para carregar no arquivo de scores
    m_palavras_acertadas.push_back(m_palavra_atual);

    while (b)
    {
        std::cout << "Deseja continuar jogando [S/N]: ";
        std::cin >> op;
        if (op == "S" || op == "N")
            b = false;
        else
            std::cout << "Tente novamente. Entrada Inválida." << std::endl;
    }

    std::cout << std::endl;
    std::cout << "------------------------------------------------------------------------------------------" << std::endl;
    
    if (op == "S")
        return true;

    return false;
}

void Forca::print_acertou_todas_palavras(){
    std::vector<std::string> dificuldades = {"Fácil", "Médio", "Difícil"};

    std::cout << "Um feito para poucos! Muito bem! Você acertou todas as palavras do nível "<< dificuldades[m_dificuldade] << "!" << std::endl;

    if(m_dificuldade != Forca::DIFICIL)
    std::cout << "Tente na dificuldade "<< dificuldades[m_dificuldade+1] << " da próxima vez! Vou ficar no aguardo! Até a próxima!" << std::endl << std::endl;
    else
    std::cout << "Genial! Parabéns pela dedição, amor e esforço pela forca! Quem sabe um dia teremos um campeonato internacional de forca" << std::endl << std::endl;

    std::cout << "(Não deixe de conferir o \"Menu de Scores\" para conferir seu feito!)" << std::endl;
    std::cout << "------------------------------------------------------------------------------------------" << std::endl;

}
  
bool Forca::rodada_terminada()
{
    // A rodada termina ou quando não existem mais tentativas ou quando o jogador vence

    if (m_palavra_atual == m_palavra_jogada)
        return true;

    if (m_tentativas_restantes != 0)
        return false;

    return true;
}

// Método para observar se o sorteio das palavras do jogo funcionou
void Forca::print_filtradas()
{
    for (int ii = 0; ii < (int)m_palavras_do_jogo.size(); ii++)
        std::cout << ii << ": " << m_palavras_do_jogo[ii] << std::endl;
}

void Forca::reset_rodada()
{  
  //Tira a última palavra do vetor pq a palavra atual do jogo é definida como a     última
  m_palavras_do_jogo.pop_back();

  //Limpa os palpites da última tentativa
  m_letras_palpitadas.clear();

  m_palavra_jogada = "";
  
  //Tentativas restantes padrão
  m_tentativas_restantes = 6;
}

void Forca::reset_all(){
    reset_rodada();
    m_palavras_acertadas.clear();
    m_pontos = 0;
}

void Forca::registrar_score(){
    std::vector<std::string> dificuldades = {"Facil", "Medio", "Dificil"};
    //score_formatted: 'Dificuldade' ; 'Nome' ; ['Palavras'] ;
    std::string score_formated, nome;

    //Dificuldade
    score_formated = dificuldades[m_dificuldade] + ";";
    
    //Nome
    std::cout <<  "Qual nome quer colocar no \"Menu de Scores\"? ";
    std::cin >> nome;
    score_formated = score_formated + nome + ";";

    std::cout << "------------------------------------------------------------------------------------------" << std::endl;
    
    //Palavras acertadas
    int ii = 0;
    while(ii < (int) m_palavras_acertadas.size())
    {
        if(ii != (int) m_palavras_acertadas.size()-1)
            score_formated.append(m_palavras_acertadas[ii] + ",");
        else
            score_formated.append(m_palavras_acertadas[ii]);
            
        ++ii;
    }
    score_formated.append(";");

    //Pontos
    score_formated = score_formated + std::to_string(m_pontos);

    //Carregar para o arquivo de scores
    std::ofstream ofs (m_arquivo_scores, std::ios_base::app);
    ofs << "\n";
    ofs << score_formated;
    ofs.close();

}
  
std::string Forca::get_palavra_jogada()
{
    return m_palavra_jogada;
}

std::string Forca::get_palavra_atual()
{
    return m_palavra_atual;
}

bool Forca::restam_palavras(){
    if( (int) m_palavras_do_jogo.size() == 0) return false;
    return true;
}