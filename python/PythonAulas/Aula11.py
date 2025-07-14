"""
Cores no Terminal:
ANSI = começa com contra barra(\) e é um escape sequence
começa com cores = \033[m e \033[0;33;44m
                 = \033[style:text:back m
códigos para style = 0(sem estilo), 1(negrito), 4(sublinhada), 7(inverter as configuracões de fundo e lrtra)

CORES NORMAIS de TEXTO:            CORES DE FUNDO:
    'vermelho':'\033[31m',         'vermelho':'\033[41m',
    'azul':'\033[34m',             'azul':'\033[44m',
    'amarelo':'\033[33m',          'amarelo':'\033[43m',
    'branco':'\033[30m',           'branco':'\033[40m',
    'roxo':'\033[35m',             'roxo':'\033[45m',
    'verde':'\033[32m',            'verde':'\033[42m',
    'ciano':'\033[36m',            'ciano':'\033[46m',
    'limpa':'\033[37m',            'limpa':'\033[47m',
    'preto e branco':'\033[7;30;m',

CORES EM NEGRITO:
    'vermelho em negrito':'\033[1;31m',
    'azul em negrito':'\033[1;34m' ,
    'amarelo em negrito':'\033[1;33m' ,
    'branco em negrito':'\033[1;30m',
    'roxo em negrito':'\033[1;35m',
    'verde em negrito':'\033[1;32m',
    'ciano em negrito':'\033[1;36m',

CORES SUBLINHADAS:
    'vermelho sublinhado':'\033[4;31m',
    'azul sublinhado':'\033[4;34m',
    'amarelo sublinhado':'\033[4;33m',
    'branco sublinhado':'\033[4;30m',
    'roxo sublinhado':'\033[4;35m',
    'verde sublinhado':'\033[4;32m',
    'ciano sublinhado':'\033[4;36m'
"""
print('\033[4;30;44mbaby baby do biro baby\033[m')

a = 3
b = 5
print('Os valores são \033[32m{}\033[m e \033[34m{}\033[m'.format(a, b))

nome = 'Rodrigo'
print('Olá {}{}{}'.format('\033[4;36;45m', nome, '\033[m'))

cores = {    #cores normais

         'vermelho': '\033[31m',
         'azul': '\033[34m',
         'amarelo': '\033[33m',
         'branco': '\033[30m',
         'roxo': '\033[35m',
         'verde': '\033[32m',
         'ciano': '\033[36m',
         'limpa': '\033[m',
         'preto e branco': '\033[7;30;m'}

nom1 = 'trinton'
print('Hello {}{}{}'.format(cores['amarelo'], nom1, cores['limpa']))
