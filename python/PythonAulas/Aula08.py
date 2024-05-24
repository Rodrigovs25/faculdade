"""
MÒDULOS:
from 'math' import 'sqrt' -> vai importar somente essa função
impot 'math' -> vai importar todas as funções de math
Funções de math:
ceil      -> arredondar pra cima
floor     -> arredondar pra baixo
trunc     -> eliminar as casas decimais
pow       -> potência do número
sqrt      -> calcular raiz quadrado
factorial -> fatorar um número
cgi: programação de páginas dinâmicas para a Web

ftplib: montagem de scripts para interação com servidores FTP

gzip: leitura e escrita de arquivos comprimidos

math: funções matemáticas (trigonometria, logaritmos etc.)

re: buscas de texto avançadas com expressões regulares (como na linguagem Perl)

string: operações com strings, incluindo conversões de listas

time: hora atual e conversão de formatos de data

xmllib: interpretação de arquivos em formato XML
"""
import math
num = int(input('Digite um número inteiro: '))
raiz = math.sqrt(num)
print('A raiz de {} é igual a {:.2f}'.format(num, raiz))


#import math
#num = int(input('Digite um número inteiro: '))
#raiz = math.sqrt(num)
#print('A raiz de {} é igual a {}'.format(num, math.floor(raiz)))

from math import sqrt
num1 = int(input('Digite um outro número inteiro:'))
raiz = sqrt(num1)
print('A raiz de {} é igual a {:.2f}'.format(num1, raiz))

#from math import sqrt, floor
#num1 = int(input('Digite um outro número inteiro:'))
#raiz = sqrt(num1)
#print('A raiz de {} é igual a {:.2f}'.format(num1, floor(raiz)))

import random                # random.random() = escolhe um número entre 0 e 1.
num2 = random.randint(1, 10) # randint = escolhe um número inteiro.
print(num2)

import emoji
print(emoji.emojize("Python is fun :red_heart:",variant="emoji_type"))

import emoji
print(emoji.emojize(':umbrella:'))

import emoji
