#include <iostream>
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
    // Contador de linhas do arquivo
    int i = 1;

    while (std::getline(fin, line))
    {
        std::istringstream linha(line);
      
        std::string palavra;
        std::getline(linha, palavra, '\t');
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
      
        std::string frequencia_string;
        std::getline(linha, frequencia_string);
        if (frequencia_string.size() != 0)
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
    // Lendo as linhas do arquivo reutilizando a variável "line"
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
    while (std::getline(fin, line))
    {
        std::istringstream linha(line);
      
        std::string palavra;
        std::getline(linha, palavra, '\t');
        std::string upper = palavra;
        // transformando a palavra para caixa alta e salvando em "upper"
        transform(palavra.begin(), palavra.end(), upper.begin(), ::toupper);

        std::string frequencia_str;
        std::getline(linha, frequencia_str);
        int frequencia = stoi(frequencia_str);

        // adicionando o par de palavra e frequencia no fim do vetor m_palavras
        m_palavras.push_back(std::pair<std::string, int>(upper, frequencia));
    }

    fin.close();

    calcular_frequencia_media();
}

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

            /** A função std::find() busca um valor no vetor e retorna um iterator para a determinada
             * posição, caso encontre-o. Do contrário, ou seja, a palavra não existir no vetor std::find
             * retorna vector<>.end().
             */
            if ((int)m_palavras_do_jogo.size() == 0 || it == m_palavras_do_jogo.end())
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
                if ((int)m_palavras_do_jogo.size() == 0 || it == m_palavras_do_jogo.end())
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
            if ((int)m_palavras_do_jogo.size() == 0 || it == m_palavras_do_jogo.end())
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
                if ((int)m_palavras_do_jogo.size() == 0 || it == m_palavras_do_jogo.end())
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
            if (((int)m_palavras_do_jogo.size() == 0 || it == m_palavras_do_jogo.end()) && (int)m_palavras_do_jogo.size() != qtd_filtradas)
            {
                m_palavras_do_jogo.push_back(m_palavras[i].first);
            }
            else if ((int)m_palavras_do_jogo.size() == qtd_filtradas)
                break;
        }
    }
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

bool Forca::validar_palpite(std::string palpite){
    
    if(palpite.size() != 1) return false;
    if( (palpite[0] < 'A' || palpite[0] > 'Z')) return false;

    return true;
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
    std::cout <<  "Qual nome quer colocar no \"Menu de Scores\"? (30 caractéres)";
    
    //Aceitar nome composto
    std::cin.ignore();
    std::getline(std::cin, nome);
    
   //Validar nome de entrada
    bool valido = false;
    while(!valido)
    for (char &ch : nome)
    {
      valido = true;
      if (ch == ';'){
                  std::cout <<  "Nome inválido. Escolha um sem \";\". Nome:  " ;
                  std::getline(std::cin, nome);
                  valido = false;
                  break;
            }
      }
    
    //Caso o nome do usuário seja maior que 30 caracteres, limitar o nome para os 30 primeiros digitados.
    if((int) nome.size() > 30) nome.resize(30);

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

bool Forca::restam_palavras(){
    if( (int) m_palavras_do_jogo.size() == 0) return false;
    return true;
}
  

std::string Forca::get_palavra_jogada()
{
    return m_palavra_jogada;
}

std::string Forca::get_palavra_atual()
{
    return m_palavra_atual;
}

std::string Forca::get_arquivo_scores(){
    return m_arquivo_scores;
}

int Forca::get_tentativas_restantes(){
    return m_tentativas_restantes;
}

std::vector<char> Forca::get_letras_palpitadas(){
    return m_letras_palpitadas;
}

int Forca::get_pontos(){
    return m_pontos;
}

Forca::Dificuldade Forca::get_dificuldade(){
    return m_dificuldade;
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

void Forca::set_palavras_acertadas(std::string palavra){
    m_palavras_acertadas.push_back(palavra);
}

void Forca::set_palavra_jogada()
{
    for (int i = 0; i < m_palavra_atual.length(); i++)
    {
        if (m_palavra_atual[i] == ' ') m_palavra_jogada.push_back(' ');
        else if (m_palavra_atual[i] == '-') m_palavra_jogada.push_back('-');
        else m_palavra_jogada.push_back('_');
    }
}
