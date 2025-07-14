a = int(input('digite um número:'))
b = int(input('digite outro número:'))
s = a + b
# print('A soma entre', a, 'e', b, 'vale', s)
print('A soma entre {} e {} vale {}' .format(a, b, s))
"""
Quantro tipos primitivos:
int = números inteiros -> 7
float = números decimais -> 15.3 and 7.0
bool = só aceitar dois valores -> True and False
str = só aceitar variáveis entre aspas -> 'oi' and '7.5'

print('A soma vale' ,s)
print('A soma vale {}' .format(s))
"""
n1 = input('Digite um valor:')
print(type(n1))