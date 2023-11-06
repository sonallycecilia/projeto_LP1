cmake_minimum_required(VERSION 3.0)
project(projeto_klaudio)

# Adicione os arquivos fonte que você deseja compilar
set(SOURCES utils/functions/functions.c main.c)

# Defina o executável de saída
add_executable(meuPrograma ${SOURCES})
