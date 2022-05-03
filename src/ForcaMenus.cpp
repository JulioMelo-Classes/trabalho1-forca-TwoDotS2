#include "../include/ForcaMenus.hpp"

ForcaMenus::ForcaMenus(Forca *forca){
    m_forca = forca;
}

int ForcaMenus::print_menu_informacoes()
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

Forca::Dificuldade ForcaMenus::print_menu_dificuldades()
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
        d = Forca::FACIL;
    if (escolha == 2)
        d = Forca::MEDIO;
    if (escolha == 3)
        d = Forca::DIFICIL;

    return d;
}

void ForcaMenus::print_scores_registrados()
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
    fin.open(m_forca->get_arquivo_scores());

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

//<! Referência: https://github.com/AngularsCoding/Hangman/blob/main/Hangman.cpp
void ForcaMenus::print_hangman(){
    std::cout << "Resta(m) " << m_forca->get_tentativas_restantes() << " tentativa(s)" << std::endl; 
    std::cout << std::endl;
	std::cout << "  -----" << std::endl;
	std::cout << "  |   |" << std::endl; 
	std::cout << "  |";    if(m_forca->get_tentativas_restantes()<=5) std::cout<<"   O"; std::cout<<std::endl;
	std::cout << "  |";    if(m_forca->get_tentativas_restantes()<=4) std::cout<<"  /"; if(m_forca->get_tentativas_restantes()<=3) std::cout<<"|"; if(m_forca->get_tentativas_restantes()<=2) std::cout<<"\\"; std::cout<<std::endl;
	std::cout << "  |";    if(m_forca->get_tentativas_restantes()<=1) std::cout<<"  / "; if(m_forca->get_tentativas_restantes()<=0) std::cout<<"\\"; std::cout<<std::endl;
	std::cout << "  |"   << std::endl; 
	std::cout << "__|__" << std::endl << std::endl;;
}

std::string ForcaMenus::print_forca_ui()
{
    std::cout << "------------------------------------------------------------------------------------------" << std::endl;
    //std::cout << "(Palavra atual: " << m_forca->get_palavra_atual() << " )" << std::endl;
    std::cout << "Lista de Palpites: " << std::endl;
    std::cout << "[ ";
    for (int ii = 0; ii < (int)m_forca->get_letras_palpitadas().size(); ++ii)
    {
        if (ii == (int)m_forca->get_letras_palpitadas().size() - 1)
            std::cout << m_forca->get_letras_palpitadas()[ii];
        else
            std::cout << m_forca->get_letras_palpitadas()[ii] << ", ";
    }
    std::cout << " ]" << std::endl << std::endl;

    std::string palpite;
    
    print_hangman();

    //Printar a palavra jogada
    for (int ii = 0; ii < (int)m_forca->get_palavra_jogada().size(); ++ii)
    {
        if (ii != (int)m_forca->get_palavra_jogada().size() - 1)
            std::cout << m_forca->get_palavra_jogada()[ii] << " ";
        else
            std::cout << m_forca->get_palavra_jogada()[ii];
    }
    std::cout << std::endl;

    std::cout << "Pontos: " << m_forca->get_pontos() << std::endl;
    std::cout << "Palpite: ";
    
    std::cin >> palpite;

    std::cout << std::endl;

    while(!m_forca->validar_palpite(palpite)){
        std::cout << "Palpite Inválido. Digite novo palpite:" << std::endl;
        std::cout << "Palpite: ";
        std::cin >> palpite; 
    }

    return palpite;
}

std::string ForcaMenus::print_forca_ui(std::pair<bool, bool> palpite, std::string ultimo_palpite)
{
    std::cout << "------------------------------------------------------------------------------------------" << std::endl;
    //std::cout << "(Palavra atual: " << m_forca->get_palavra_atual() << " )" << std::endl;
    std::cout << "Lista de Palpites: " << std::endl;

    std::cout << "[ ";
    for (int ii = 0; ii < (int)m_forca->get_letras_palpitadas().size(); ++ii)
    {
        if (ii == (int)m_forca->get_letras_palpitadas().size())
            std::cout << m_forca->get_letras_palpitadas()[ii];
        else
            std::cout << m_forca->get_letras_palpitadas()[ii] << ", ";
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

    //Printar a palavra jogada
    for (int ii = 0; ii < (int)m_forca->get_palavra_jogada().size(); ++ii)
    {
        if (ii != (int)m_forca->get_palavra_jogada().size() - 1)
            std::cout << m_forca->get_palavra_jogada()[ii] << " ";
        else
            std::cout << m_forca->get_palavra_jogada()[ii];
    }
    std::cout << std::endl;

    std::string str;
    std::cout << "Pontos: " << m_forca->get_pontos() << std::endl;
    std::cout << "Palpite: ";
    std::cin >> str;

    std::cout << std::endl;

    while(!m_forca->validar_palpite(str)){
        std::cout << "Palpite Inválido. Digite novo palpite:" << std::endl;
        std::cout << "Palpite: ";
        std::cin >> str; 
    }

    return str;
}

void ForcaMenus::print_game_over()
{
   std::cout << "------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "O jogo acabou, a palavra era " << m_forca->get_palavra_atual() << "!" << std::endl;
    print_hangman();
    std::cout << "Pontos: " << m_forca->get_pontos() << std::endl;
    std::cout << "Mais sorte na próxima! " << std::endl;
}

bool ForcaMenus::print_continuar_jogando()
{
    std::string op;
    bool b = true;
    
    std::cout << "------------------------------------------------------------------------------------------" << std::endl;

    std::cout << "Você acertou! Parabéns! A palavra era " << m_forca->get_palavra_atual() << "!" << std::endl
              << std::endl;

    std::cout << "------------------------------------------------------------------------------------------" << std::endl << std::endl;
   
    //Salva palavra acertada para carregar no arquivo de scores
    m_forca->set_palavras_acertadas(m_forca->get_palavra_atual());

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

void ForcaMenus::print_acertou_todas_palavras(){
    std::vector<std::string> dificuldades = {"Fácil", "Médio", "Difícil"};

    std::cout << "Um feito para poucos! Muito bem! Você acertou todas as palavras do nível "<< dificuldades[m_forca->get_dificuldade()] << "!" << std::endl;

    if(m_forca->get_dificuldade() != Forca::DIFICIL)
    std::cout << "Tente na dificuldade "<< dificuldades[m_forca->get_dificuldade()+1] << " da próxima vez! Vou ficar no aguardo! Até a próxima!" << std::endl << std::endl;
    else
    std::cout << "Genial! Parabéns pela dedição, amor e esforço pela forca! Quem sabe um dia teremos um campeonato internacional de forca" << std::endl << std::endl;

    std::cout << "(Não deixe de conferir o \"Menu de Scores\" para conferir seu feito!)" << std::endl;
    std::cout << "------------------------------------------------------------------------------------------" << std::endl;
}