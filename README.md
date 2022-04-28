# Avaliação e Feeback

- Implementação do carregamento dos arquivos |  6 / 10 pontos
    - O carregamento do arquivo de scores está ok, mas o arquivo de palavras não suporta palavras com espaço, tipo "Sao Paulo 131321"

- Implementação de parte da validação | 10 / 10 pontos
    - A validação está quase toda completa não é? Acho que só modificando para suportar palavras com espaço já deve terminar.

- Implementação de um main funcional com parte da UI | 5 / 5 pontos

- Implementação de parte da lógica de sorteio de palavras | 10 / 10 pontos 
    - Mutio boa a ideia de usar std::shuffle realmente é uma das melhores formas de fazer esse quesito
    - Não entendi muito bem a lógica do preenchimento de m_palavras_jogadas, embora vá funcionar (não tem como não funcionar!)

- Estrutura básica dos arquivos e processo de compilação definido | 5 / 5 pontos
    - A forma como vc inclui o forca.hpp está errada, embora funcione pra compilar... O melhor aqui é você usar alguma ferramenta de
    compilação automática, veja o exemplo que eu fiz com o cmake.

- Observações gerais
    - Acho que vc poderia modularizar melhor separando essa parte de interface em outro .hpp ao invés de incluir tudo na classe forca

# Trabalho-1

Repositório contendo as especificações do Trabalho 1 da disciplina de LP1

# Documento de Especificação

Leia o documento de especificação contido em [Especificação do Trabalho 1](https://docs.google.com/document/d/1aa51VNLQ_jpZaEuGkMz2KE8feAkE48-TENZ9eqn48nk/edit?usp=sharing). Preencha o autor.md com as informações relativas ao grupo/autor.

# 1. Como compilar e executar o projeto:

- Compilar pra arquivos ".o": g++ -c src/main.cpp src/Forca.cpp
- Juntar os arquivos ".o" num executável: g++ -o forca main.o Forca.o
- Executar o executável passando os arquivos como argumento: ./forca ./resources/words_2000.txt ./resources/scores.txt

# 2. Testes e saídas esperadas

## 2.1. Testes do arquivo de palavras

**Tentativa de abrir um arquivo de palavras não existente.**

- Execução:

`./forca ./resources/words.txt ./resources/scores.txt `

- Saída esperada:

`>>> Erro! Nenhum arquivo de palavras foi encontrado em: ./resources/words.txt`

**Tentativa de abrir um arquivo de palavras contendo caracteres que não estejam entre [a- z|A - Z] , ‘(espaço em branco) ou hífen ‘-’.**

- Execução:

`./forca ./resources/testePalavras-caractereInvalido.txt ./resources/scores.txt`

- Saída esperada:

`>>> Erro! Caractere inválido localizado na palavra: tçmbem (linha 1)`

**Tentativa de abrir um arquivo de palavras contendo uma palavra de tamanho menor ou igual a 4.**

- Execução:

`./forca ./resources/testePalavras-palavraInvalida.txt ./resources/scores.txt`

- Saída esperada:

`>>> Erro! Palavra com tamanho menor ou igual a 4: piu (linha 1)`

**Tentativa de abrir um arquivo de palavras sem frequência.**

- Execução:

`./forca ./resources/testePalavras-semfrequencia.txt ./resources/scores.txt`

- Saída esperada:

`>>> Erro! Não existe frequência referente à palavra: Brasil (linha 1)`

**Tentativa de abrir um arquivo de palavras com uma frequência não pertencente aos inteiros positivos.**

- Execução:

`./forca ./resources/testePalavras-frequenciaInvalida.txt ./resources/scores.txt`

- Saída esperada:

`>>> Erro! Frequência não é um número inteiro positivo na palavra: tambem (linha 1)`

## 2.2. Testes do arquivo de scores

**Tentativa de abrir um arquivo de scores não existente.**

- Execução:

`./forca ./resources/words_2000.txt ./resources/scoresTest.txt`

- Saída esperada:

`>>> Erro! Nenhum arquivo de scores foi encontrado em: ./resources/scoresTest.txt`

**Tentativa de abrir um arquivo de scores com a presença de mais ou menos ';' em alguma linha.**

- Execução:

`./forca ./resources/words_2000.txt ./resources/testeScores-erroScores.txt`

- Saída esperada:

`>>> Erro! Presença de 4 ';' na linha 1 do arquivo de scores [Esperado: 3]`

**Tentativa de abrir um arquivo de scores com o campo "nível de dificuldade” vazio.**

- Execução:

`./forca ./resources/words_2000.txt ./resources/testeScores-dificuldadeVazio.txt`

- Saída esperada:

`>>> Erro! Campo Nível de dificuldade vazio no arquivo de scores (linha 1)`

**Tentativa de abrir um arquivo de scores com o campo "nome” vazio.**

- Execução:

`./forca ./resources/words_2000.txt ./resources/testeScores-nomeVazio.txt`

- Saída esperada:

`>>> Erro! Campo Nome vazio no arquivo de scores (linha 1)`


**Tentativa de abrir um arquivo de scores com o campo "pontuação” vazio.**

- Execução:

`./forca ./resources/words_2000.txt ./resources/testeScores-pontuacaoVazio.txt`

- Saída esperada:

`>>> Erro! Campo Score vazio no arquivo de scores (linha 1)`
