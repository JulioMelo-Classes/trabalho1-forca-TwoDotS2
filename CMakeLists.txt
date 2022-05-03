cmake_minimum_required(VERSION 3.10)
project(Forca VERSION 2.0)

#diretório onde os arquivos include estão
#se o diretório estiver aqui você deve
#incluir o arquivo com #include "arq.hpp"
#como se ele estivesse no mesmo diretório que
#os .cpp
include_directories(./include)

#cria um executável com nome "program"
#que depende de todos os .cpp
add_executable(	program
								src/main.cpp
								src/Forca.cpp)
