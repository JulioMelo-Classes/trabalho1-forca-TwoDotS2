// Bibliotecas para o transform
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

// Bibliotecas para o sorteio
#include <ctime>   // std::time
#include <cstdlib> // std::rand, std::srand

class Forca
{
public:
    enum Dificuldade
    {
        FACIL,
        MEDIO,
        DIFICIL
    };

private:
    // TODO: armazenar os scores?

    std::vector<std::pair<std::string, int>> m_palavras; //<! palavras e sua ocorrência no Corpus

    std::string m_arquivo_scores; //<! nome do arquivo contendo os scores

    std::string m_arquivo_palavras; //<! nome do arquivo contendo as palavras

    Dificuldade m_dificuldade = Dificuldade::FACIL; //<! dificuldade atual do jogo

    std::vector<std::string> m_palavras_do_jogo; //<! container “Palavras do Jogo”. Onde será armazenado as palavras do sorteio
    std::vector<char> m_letras_palpitadas;       //<! contem as letras palpitadas pelo jogador
    std::string m_palavra_atual;                 //<! palavra sendo jogada “atualmente”
    std::string m_palavra_jogada;                //<! palavra sendo jogada “atualmente” no formato “_ _ _ ... _ “
    std::vector<std::string> m_palavras_acertadas;
    int m_tentativas_restantes; // TODO: armazenar tentativas restantes
    int m_frequencia_media;     // Armazenar a frequência média de palavras
    int m_pontos;     // Armazenar a frequência média de palavras

public:

    /**
     * Cria um objeto Forca
     * O construtor pode ou não validar os arquivos de entrada, no entanto, mesmo com
     * os arquivos inválidos o objeto deve ser construído. Para o caso de arquivos de palavras
     * ou scores inválidos, use o método eh_valido.
     * @param palavras o arquivo que contém as palavras
     * @param scores o nome do arquivo que contém os scores
     * @see eh_valido
     */

    Forca(std::string __palavras, std::string __scores);

    /////////////////////////////////////////////////////////////////////////
    /////////// Validação
    //////////////////////////////////////////////

    /**
     * Carrega os arquivos de scores e palavras preenchendo **ao menos** a estrutura m_palavras
     */
    void carregar_arquivos();

    /**
     * Valida os arquivos de entrada de acordo com as especificações.
     * Ao validar os arquivos, no caso de arquivos inválidos, este método deve retornar a
     * razão correspondente de acordo com as especificações.
     * @return {T,""} se os arquivos estiverem válidos, {F,"razão"} caso contrário.
     */

    std::pair<bool, std::string> eh_valido();

    /////////////////////////////////////////////////////////////////////////
    /////////// Atualização de estados
    //////////////////////////////////////////////

    /**
     * Retorna a próxima palavra de acordo com a dificuldade atual.
     * Este método deve atualizar o valor dos atributos m_palavra_atual, com a palavra atual,
     * do atributo m_palavra_jogada com um texto no formato "_ _ _ _ ... _".
     * O método também deve sortear as letras que devem aparecer dependendo do nível de dificuldade,
     * alterando o valor de m_palavra_jogada de acordo.
     * @return o valor do atributo m_palavra_jogada.
     */
    void proxima_palavra();

    /**
     * Testa se uma letra pertence á palavra atual e se já foi jogada pelo jogador.
     * Este método testa se uma letra pertence à palavra atual, caso a letra pertença a palavra
     * e ainda não foi jogada o método retorna {T, T}, caso a letra não pertença à palavra o método retorna {F,T};
     * Caso a letra já tenha sido jogada o método retorna {T, F}, quando a letra pertence à palavra e {F, F}, quando
     * não pertence.
     * Este método deve atualizar os atributos m_tentativas, m_palavra_jogada e m_letras_palpitadas, para refletir
     * as situações citadas. No caso da letra já ter sido escolhida, o método não deve atualizar m_tentativas.
     * @param palpite uma letra, que deve ser testada se pertence à palavra.
     * @return {T,T} se o palpite pertence à palavra e é um palpite novo, 
     *         {T,F} no caso do palpite pertencer à palavra, mas não é novo.
     *         {F,T} caso não pertença e é novo.
     *         {F,F} no caso do palpite não pertencer à palavra e não é novo.
     */
    std::pair<bool, bool> palpite(std::string palpite);

    /**
     * Em caso de Game Over ou do jogador ter acertado a palavra este método deve retornar T.
     * @return T caso o m_tentativas_restantes do jogo esteja igual a 0 ou se o usuário
     *         acertou toda a palavra, F caso contrário.
     */

    bool rodada_terminada();

    /**
     * Atualiza quantas tentativas ainda são possíveis, dado o tipo de palpite ({T, T}, {T,F}, {F, F} ou {F,T}), 
     * realizando a alteração do valor de m_tentativas_restantes.
     * 
     * @param tipo_palpite baseado no modelo de retorno de palpite().
     * @see palpite
     */
    void atualizar_tentativas( std::pair<bool, bool> tipo_palpite);


    /**
     * Atualizar os pontos baseado no tipo de palpite ({T, T}, {T,F}, {F, F} ou {F,T}), alternado o valor de m_pontos
     * 
     * @param tipo_palpite baseado no modelo de retorno de palpite().
     * @see palpite
     */
    void atualizar_pontos(std::pair<bool, bool> tipo_palpite, std::string ultimo_palpite);

    
    /**
     * Caso o jogador perca ou acerte a palavra da rodada e decida sair, pede ao usuário que escolha um nome e registra o score
     * em m_arquivo_scores.
     */
    void registrar_score();
    
    /**
     * Reseta o valor de tentativas restantes para 6 e do atributo m_letras_palpitadas para vazio
     * Este método é útil no caso do jogador escolher continuar o jogo, ou no início
     * de cada rodada, resetando o valor de tentativas restantes para 6 e do atributo
     * m_letras_palpitadas como sendo um vetor vazio
     */
    void reset_rodada();

    /**
     * Chama a função reset_rodada, mas também faz o reset de m_pontos e m_palavras_acertadas
     */
    void reset_all();

    /////////////////////////////////////////////////////////////////////////
    /////////// Sorteio
    //////////////////////////////////////////////

    /**
     * Definir o valor médio da frequência das palavras. Soma todas as frequências de m_palavras e realiza uma média aritimética,
     * atribuindo valor à m_frequencia_media.
     *
     */
    void calcular_frequencia_media();

    /**
     * Define as palavras do container de "Palavaras do Jogo" (m_palavras_do_jogo). A aletoriedade vem da ordenação de
     * do vetor m_palavras através do método std::random_shuffle() e de um número aleatório baseado no retorno de shuffle e rand.
     * 
     * @see http://www.cplusplus.com/reference/algorithm/random_shuffle/
     * */
    void sortear_palavras();

    /**
     * Essa função serve para gerar os valores previstos por 3b) iii. e 3c) iii.
     * O nome dica vem do propósito da função, que é o de auxiliar o jogador nas primeira rodada exibindo algumas das letras da
     * m_palavra atual. Varia de acordo com a dificuldade. 
     */
    void dica_palavra_jogada();


    /**
     * Valida o palpite verificando se está entre o intervalo A e Z é válido.
     * 
     * @return T, caso seja válido.
     *         F, caso tenha mais de um caracter ou está fora do intervalo.
     */
    bool validar_palpite(std::string palpite);

    /**
     * Função para auxiliar no teste manual do sorteio das palavras de m_palavras_do_jogo geradas por sortear_palavras()
     * @see sortear_palavras
     */
    void print_filtradas();

    /////////////////////////////////////////////////////////////////////////
    /////////// Getters e Setters
    //////////////////////////////////////////////

    /**
     * Verifica se ainda existem palavras em m_palavras_do_jogo. Essa função é muito importante para o sistema, uma vez
     * que a lógica de troca da palavra_atual é a remoção do última palavra de m_palavras_do_jogo
     * @return F, caso o tamanho m_palavras_do_jogo é igual a zero,
     *         T, caso contrário.
     * 
     * OBS.: é um "getter de estado".
     */
    bool restam_palavras();


    /**
     * Retorna o caminho do arquivo de scores.
     * @return o caminho do arquivo de scores.
     */
    std::string get_arquivo_scores();

    /**
     * Retorna a palavra atual que está sendo jogada.
     * Diferente do método proxima_palavra(), este método __não atualiza__ o atributo
     * m_palavra_atual, apenas retorna o atributo m_palavra_jogada que é a palavra no
     * formato  "_ _ _ _ ... _" contendo todas as letras
     * já acertadas/sorteadas ao invés de “_”.
     * @return a palavra atualmente sendo jogada.
     */
    std::string get_palavra_jogada();

    /**
     * Retorna o valor da palavra atual, útil no caso de um game over, para mostrar a palavra que estava
     * sendo jogada
     * @return o valor do atributo palavra_atual
     **/
    std::string get_palavra_atual();

     /**
     * Retorna o valor de m_tentativas_restantes.
     * @return o valor de m_tentativas_restantes
     */
    int get_tentativas_restantes();

     /**
     * Retorna o valor de m_letras_palpitadas.
     * @return o valor de m_letras_palpitadas
     */
    std::vector<char> get_letras_palpitadas();
    
    /**
     * Retorna o valor de m_pontos.
     * @return o valor de m_pontos
     */
    int get_pontos();

    /**
     * Retorna o valor de m_dificuldade.
     * @return o valor de m_dificuldade
     */
    Dificuldade get_dificuldade();

    /**
     * Modifica a dificuldade do jogo.
     * Este método modifica a dificuldade do jogo gerando um novo vetor palavras_do_jogo
     * toda vez que é chamado.
     * @param d a dificuldade desejada
     * @see proxima_palavra
     */
    void set_dificuldade(Dificuldade d);

    /**
     * Adiciona ao vetor m_palavras_acertadas a palvra acertada.
     * Método auxiliar para o registro de scores do jogo.
     * @param palavra a palavra acertada;
     * @see proxima_palavra
     */
    void set_palavras_acertadas(std::string palavra);

private:
    //<! As funções inserir_filtradas_(dificuldade) auxiliam na modularização de inserir
    /**
     * O objetivo dessa função é tornar mais legível a função sortear_palavras().
     * 'inserir_filtradas_facil' serve para salvar as palavras da base de acordo com a condição 'Fácil'
     * @param qtd_filtradas
     */
    void inserir_filtradas_facil(int qtd_filtradas);
        
    /**
     * O objetivo dessa função é tornar mais legível a função sortear_palavras().
     * 'inserir_filtradas_medio' serve para salvar as palavras da base de acordo com a condição 'Médio'
     * @param qtd_filtradas
     */
    void inserir_filtradas_medio(int qtd_filtradas);

    /**
     * O objetivo dessa função é tornar mais legível a função sortear_palavraas().
     * 'inserir_filtradas_dificil' serve para salvar as palavras da base de acordo com a condição 'Difícil'
     * @param qtd_filtradas
     */
    void inserir_filtradas_dificil(int qtd_filtradas);

    /** Define o valor de m_palavra atual.
     * Auxiliar da função proxima_rodada();
     * @see proxima_rodada
     */
    void set_palavra_atual(std::string p);

    /**
     * Escrever a m_palavra_jogada no formato _ _ _ ... _. É um método privado porque sempre que m_palavra_atual for definida
     * por proxima_palavra(), é direta a necessidade de definir m_palavra_jogada.
     */
    void set_palavra_jogada();

};
