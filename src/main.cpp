#include "../include/Forca.hpp"
#include <iostream>

using namespace std;
int main(int argc, char *argv[])
{
    Forca forca(argv[1], argv[2]);

    auto valid = forca.eh_valido();
    cout << ">>> Lendo arquivo de palavras [" << argv[1] << "] e scores [" << argv[2] << "], por favor, aguarde..." << endl;
    cout << "--------------------------------------------------------------------" << endl;
    if (!valid.first)
    { // sai do programa ao encontrar um erro
        cout << ">>> Erro " << valid.second << endl;
        cout << "--------------------------------------------------------------------" << endl;
        exit(-1);
    }
    else
    {
        cout << ">>> Arquivos OK! " << endl;
        cout << "--------------------------------------------------------------------" << endl;
    }
  
    forca.carregar_arquivos();
    
    /**
     * Como os arquivos são válidos, calcula a frequência média de palavras no 'Arquivo de Palavras'
     */
    
    forca.set_frequencia_media();
    
    // while (true)
    // {
    //     /*imprime o menu principal e a escolha do usuário*/
    //     forca.print_menu_informacoes(/*opcao do user*/);

    //     if (/*iniciar jogo*/)
    //     {
    //         /*Seleciona dificuldade*/
    //         forca.print_menu_dificuldades(/**/);
    //         Forca::Dificuldade d;
    //         forca.set_dificuldade(d);
    //         while (true)
    //         { //
    //             string p = forca.proxima_palavra();
    //             /*exibe interface do jogo*/
    //             while (!forca.rodada_terminada())
    //             { // loop da rodada
    //                 /*ler palpite*/
    //                 string palpite;
    //                 auto result = forca.palpite(palpite);
    //                 /*testa palpite e atualiza a interface dependendo do resultado*/
    //             }
    //             if (/*acertou a palavra inteira*/)
    //             {
    //                 /*imprime interface de continuar / parar*/
    //                 if (/*parar*/)
    //                     break;
    //                 else
    //                     forca.reset_rodada();
    //             }
    //             else
    //             { /*perdeu*/
    //                 /*imprime gameover e a palavra que estava sendo jogada*/
    //                 break;
    //             }
    //         }
    //         /*ler informações do jogador para o score e gravar no arquivo*/
    //     }
    //     else if (/*mostrar score*/)
    //         /*mostrar score*/
    //         else // qualquer outro número sai do jogo
    //             break;
    // }
    return 0;
}