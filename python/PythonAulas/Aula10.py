"""
Condiçâo:
if carro.esquerda():
    blocoTrue
else:
    blocoFalse

tempo = int(input('Quantos anos tem o seu carro?'))
if tempo <=3:
    print('Seu carro é novo')
else:
    print('Seu carro é velho')
print('--FIM--')
"""
n1 = float(input('Digite a primeira nota:'))
n2 = float(input('Digite a segunda nota:'))
n = (n1 + n2)/2
print('A sua média foi {:.1f}'.format(n))
if n >= 6.0:
    print('Sua média foi boa!')
else:
    print('Sua média foi ruim!')
print('Parabéns' if n >= 6 else 'Estude mais')
