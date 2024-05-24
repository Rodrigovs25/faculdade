"""
Fatiamento da str:
frase[9:13] = vai colocar as caracteres do 9 até o 12
frase[9] = vai colocar somente o caractere 9
frase[9:21:2] = vai colocar os caracteres 9 até o 21, pulando de 2 em 2 casas
frase[:5] = frase[0:5] = do início até o cinco
frase[15:] = do quinze até o final
frase[9::3] = do nove até o final, pulando de 3 em 3 casas

Análise da str:
len(frase) = comprimento da frase
frase.count('o') = conta quantas vezes aparece o 'o' minúsculo na sentença
frase.count('o', 0, 13) = conta quantos 'o' aparece de 0 a 12
frase.find('deo') = quantas vezes foram encontrados 'deo' e qual a posição de início
frase.rfind('') = qual é a posição final, começa a contar da direita pra esquerda
frase.find('android') = quando você colocar uma str que não existe ele coloca o valor -1
'curso' in frase = vai colocar true ou falso

Transformação da str:
frase.replace('python','android') = substituir python por android
frase.upper() = str vai ficar com letra maiúscula
frase.lower() = str vai ficar com letra minúscula
frase.capitalize() = str vai ficar com letra minúscula exceto a primeira caractere
frase.title() = vai analisar quantas palavras tem na str e, assim, as letras de todas palavras vão ficar maísculas 
frase('   aprenda python   ')
frase.strip() = vai remover todos os espaços inúteis no início e no final da cadeia
frase.rstrip() = vai remover os espaços inúteis da direita da str
frase.lstrip() = vai remover os espaços inúteis da esquerda da str

Divisão da str:
frase.split() = retirar os espaços vazios da frase e essas palavras vão para uma lista

Junção da str:
' '.join(frase) = juntar todos os elementos da frase depois da separação

OBS:para escrever longos textos sem precisar usar vários print e só utlizar três aspas
OBS:letras maisculas e minusculas são diferetes
"""

#frase = 'Curso em Vídeo Python'
#print(frase.upper().count('O'))

#frase = '     Curso em Vídeo Python    '
#print(len(frase.strip()))

#frase = 'Curso em Vídeo Python'
#frase = frase.replace('Python', 'Android')
#print(frase)

#frase = 'Curso em Vídeo Python'
#print('Curso' in frase)

#frase = 'Curso em Vídeo Python'
#print(frase.lower().find('curso'))

#frase = 'Curso em Vídeo Python'
#dividido = frase.split()
#print(' '.join(dividido))

frase = 'Curso em Vídeo Python'
dividido = frase.split()
print(dividido[2][3])
