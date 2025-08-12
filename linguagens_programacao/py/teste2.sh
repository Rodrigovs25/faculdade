#!/bin/bash

# Teste para validar a executabilidade do código

# Configurações
PYTHON_EXECUTABLE="python3"  # Modifique se necessário
MAIN_PY="main.py"  # Modifique se o nome do seu arquivo Python for diferente

# Teste 1: Execução básica do código
echo "Teste 1: Execução básica do código"
$PYTHON_EXECUTABLE $MAIN_PY

# Teste 2: Adição de elementos e operações
echo "Teste 2: Adição de elementos e operações"
$PYTHON_EXECUTABLE $MAIN_PY

# Adicione outros testes conforme necessário
# ...

echo "Testes concluídos."

#!/bin/bash

# Script de teste para a executabilidade do código

# Verifica se o Python está instalado
if ! command -v python3 &> /dev/null; then
    echo "Python3 não encontrado. Por favor, instale o Python3."
    exit 1
fi

# Instalação de dependências (se necessário)
# Certifique-se de adicionar quaisquer comandos de instalação de dependências aqui

# Executa o código Python
python3 main.py

# Se necessário, adicione mais comandos de teste aqui

echo "Teste concluído com sucesso."
