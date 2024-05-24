#!/bin/bash

# Este script de teste assume que os arquivos Conjunto.java e Main.java estão no mesmo diretório.

# Compilação do código-fonte

# Compilação da classe Conjunto
javac Conjunto.java

# Complicação do programa principal
javac main.java

# Execução do programa
echo "Teste 1: Execução básica do código"
java main

echo "Teste concluído com sucesso."
