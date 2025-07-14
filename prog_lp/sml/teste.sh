#!/bin/bash

# Compilar os arquivos SML
echo "Compilando conjunto.sml..."
ml-build conjunto.sml

echo "Compilando main.sml..."
ml-build main.sml

# Executar o programa SML
echo "Executando o programa SML..."
sml @SMLload main

echo "Teste concluído!"
