#include <Forca.hpp>

class ForcaMenus{
    
private:
    Forca *m_forca; //<! Um ponteiro para o objeto do jogo a ser instânciado no main

public:
    /**
     * Cria um objeto ForcaMenus
     */

    ForcaMenus(Forca*);

    /**
     * Printa o menu de informações do jogo da forca.
     * (Opções 'Inicar Jogo', 'Ver scores anteriores' e 'Sair do jogo')
     */
    int print_menu_informacoes();

    /**
     * Dado o arquivo de scores, printa os scores registrados.
     */
    void print_scores_registrados();

    /**
     * Printa o menu das dificuldades do jogo da forca, caso o usuário tenha selecionado a opção de iniciar o jogo. Lê a dificuldade
     * escolhida pelo jogador.
     * @return A dificuldade escolhida pelo jogador para definir a dificuldade do jogo a ser jogado.
     * (Dificuldades: 'Fácil', 'Médio' e 'Difícil)
     */
    Forca::Dificuldade print_menu_dificuldades();

    /**
     * Printa a user interface da forca baseada em m_palavra_jogada e m_palavra_atual. O método sobrecarregado tem como objetivo
     * registrar uma resposta mais completa de acordo com o último tipo do palpite retornado em palpite() dado pelo usuário. Chama
     * validar_palpite() para verificar a validade.
     * 
     * @see palpite
     * @see validar_palpite
     */
    std::string print_forca_ui();
    std::string print_forca_ui(std::pair<bool, bool> palpite, std::string ultimo_palpite);


    /**
     * Printa a tela de game over, caso o usuário perca a rodada.
     */
    void print_game_over();

    /**
     * Caso o jogador ganhe a rodada, pergunta se quer continuar jogando por mais uma rodada, até que ganhe a próxima, chamando
     *  a função novamente ou perca no meio do jogo.
     */
    bool print_continuar_jogando();

    /**
     * Atualiza o estado da pessoa enforcada caso o número de tentativas diminua - m_tentativas_restante.
     */
    void print_hangman();
    
    /**
     * Exibe um menu específico para caso o jogador acerte todas as palavras em determinada dificudade. Gera um retorno 
     * diferente por difiucldade.
     */
    void print_acertou_todas_palavras();

};
