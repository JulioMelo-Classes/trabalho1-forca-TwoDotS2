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
    
    //Lounge "Menu informações" | Nível de Acesso 0
    while ( true )
    {
        //imprime o menu principal e a escolha do usuário
        op_principal = forca.print_menu_informacoes(); //<! Qualquer opção diferente ou de 1 ou de 2 resulta  
        
        

        //Lounge "Dificuldades" | Nível de Acesso 1
        if (op_principal == 1)
        {
            Forca::Dificuldade d = forca.print_menu_dificuldades();
            forca.set_dificuldade(d);

            //Sorteia as palavras
            forca.sortear_palavras();

            //In game | Nível de Acesso 2.1
            while ( true )
            {
                //define a palavra da rodada atual e a sua forma em underscores
                forca.proxima_palavra();
                if(forca.get_palavra_atual_size() == 0) 
                {
                  forca.print_acertou_todas_palavras();
                  break;  
                }
              
                //exibe interface do jogo
                forca.dica_palavra_jogada(); 

                string palpite = forca.print_forca_ui();
                
                while (!forca.rodada_terminada())
                { // loop da rodada
                    
                    auto result = forca.palpite(palpite);

                    forca.atualizar_tentativas(result);
                    forca.atualizar_pontos(result, palpite);

                    if(forca.rodada_terminada()) break;

                    palpite = forca.print_forca_ui(result, palpite);
                }

                if (forca.get_palavra_atual() == forca.get_palavra_jogada())
                { 
                    //Lounge vitória da rodada | Nível de Acesso 3
                    //Pergunta se quer continuar jogando
                    
                    bool op = forca.print_continuar_jogando();
                    if (op)
                    {
                    //Caso o usuário decida jogar mais uma rodada
                        forca.reset_rodada();
                        //std::vector.pop()
                    }
                    else
                    {
                    //Caso o usuário decida sair
                        forca.registrar_score();
                        forca.reset_all();
                        break;
                    }
                        
                }
                else
                { //perdeu
                    forca.print_game_over();
                    forca.registrar_score();
                    break;
                }
            }
            //ler informações do jogador para o score e gravar no arquivo
        }
        
        //Lounge scores de jogatinas anteriores| Nível de Acesso 2.2
        else if (op_principal == 2)
            forca.print_scores_registrados();

        else break;
    }
    
    return 0;
}