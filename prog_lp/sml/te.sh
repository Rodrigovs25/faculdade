#!/bin/bash

# Compilar os arquivos SML
echo "Compilando conjunto.sml..."
ml-build list.sml

echo "Compilando pri.sml..."
ml-build pri.sml

# Executar o programa SML
echo "Executando o programa SML..."
sml @SMLload pri

# Limpar arquivos gerados
rm -rf list.cm pri.cm

echo "Teste concluído!"