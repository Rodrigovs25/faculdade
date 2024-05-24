from random import shuffle
a1 = str(input('Primeiro aluno: '))
a2 = str(input('Segundo aluno: '))
a3 = str(input('Terceiro aluno: '))
a4 = str(input('Quatro aluno: '))
lista = [a1, a2, a3, a4]
shuffle(lista)
print('A ordem de apresentação será:')
print(lista)
'''
sample = serão escolhidos dois entre quatro por exemplo
sample([a1, a2, a3, a4],k=2)

a1 = str(input('Digite a primeira equipe '))
a2 = str(input('Digite a segunda equipe '))
a3 = str(input('Digite a terceira equipe '))
a4 = str(input('Digite a quarta equipe '))
lista = '{}, {}, {}, {}' .format(a1,a2,a3,a4).split()
shuffle(lista)
print('A sequência escolhida foi {} '.format(lista))
'''


