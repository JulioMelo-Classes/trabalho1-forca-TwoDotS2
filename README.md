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

`./forca ./resources/words_2000.txt ./resources/scoresTest.txt`

- Saída esperada:

`>>> Erro! Nenhum arquivo de scores foi encontrado em: ./resources/scoresTest.txt`

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