#include "../include/Forca.hpp"
#include <iostream>

using namespace std;
int main(int argc, char *argv[])
{
    Forca forca(argv[1], argv[2]);
    int op_principal;

    auto valid = forca.eh_valido();
    cout << ">>> Lendo arquivo de palavras [" << argv[1] << "] e scores [" << argv[2] << "], por favor, aguarde..." << endl;
    cout << "--------------------------------------------------------------------" << endl;
    if (!valid.first)
    { // sai do programa ao encontrar um erro
        cout << ">>> Erro! " << valid.second << endl;
        cout << "--------------------------------------------------------------------" << endl;
        exit(-1);
    }
    else
    {
        cout << ">>> Arquivos OK! " << endl;
        cout << "--------------------------------------------------------------------" << endl;
    }
  
    forca.carregar_arquivos();
    
  /*
    while ( true )
    {
        //imprime o menu principal e a escolha do usuário
        op_principal = forca.print_menu_informacoes();
        
        if (op_principal == 1)
        {
            Forca::Dificuldade d = forca.print_menu_dificuldades();
            forca.set_dificuldade(d);

            //Sorteia as palavras
            forca.sortear_palavras();

            while ( true )
            {
                //define a palavra da rodada atual e a sua forma em underscores
                forca.proxima_palavra();

                //exibe interface do jogo
                forca.dica_palavra_jogada(); 
                string palpite = forca.print_forca_ui();
                
                while (!forca.rodada_terminada())
                { // loop da rodada
                    //palpite() atualiza rodada?
                    auto result = forca.palpite(palpite);
                    forca.atualizar_tentativas(result);
                    palpite = forca.print_forca_ui(result, palpite);
                }

                if (forca.get_palavra_atual() == forca.get_palavra_jogada())
                { //Pergunta se quer continuar jogando
                    bool op = forca.print_continuar_jogando();
                    if (op)
                    {
                        forca.reset_rodada();
                        //std::vector.pop()
                    }
                    else
                        break;
                        
                }
                else
                { //perdeu
                    forca.print_game_over();
                    break;
                }
            }
            //ler informações do jogador para o score e gravar no arquivo
        }
        
        else if (op_principal == 2)
            forca.print_scores_registrados();

        else break;
    }
    */
    return 0;
}