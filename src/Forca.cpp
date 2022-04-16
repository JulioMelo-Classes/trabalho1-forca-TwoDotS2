#include "Forca.hpp"

#include <iostream>
#include <vector>
#include <fstream>

std::pair<bool, std::string> eh_valido()
{
    return std::pair<bool, std::string>{};
}

/**
 * @brief Calcula através de média aritimética a média de frequência das palavras do banco  
 * 
 * @param palavras 
 * @return int 
 */

int calcular_frequencia_media( std::vector< std::pair<std::string, int> > palavras ){
    int frequencia = 0;
    int media = 0;
    
    for (int i = 0; i < (int) palavras.size(); i++)
    {
        frequencia += palavras[i].second;
    }
    
    media = frequencia/((int)palavras.size());
    
    return frequencia;
}