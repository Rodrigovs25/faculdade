ca = float(input('Digite o valor do cateto adjacente: '))
co = float(input('Digite o valor do caeto oposto: '))
hi = (ca ** 2 + co ** 2) ** (1/2)
print('A hipotenusa vale {:.2f}'.format(hi))

from math import hypot
ca1 = float(input('Digite o valor do cateto adjacente: '))
co1 = float(input('Digite o valor do caeto oposto: '))
hi1 = hypot(ca1, co1)
print('A hipotenusa vale {:.2f}'.format(hi1))