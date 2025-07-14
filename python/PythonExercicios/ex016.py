import math
a = float(input('digite um número: '))
b = math.trunc(a)
print('O número digitado foi {} e a sua porção inteira é {} '.format(a, b))

from math import trunc
a1 = float(input('Digite um outro número:'))
b1 = trunc(a1)
print('O número digitado foi {} e a sua porção inteira é {}'.format(a1, b1))

import math
num = float(input('digite um valor: '))
print('O número digitado foi {} e a sua porção inteira é {}'.format(num, math.trunc(num)))

from math import trunc
num1 = float(input('digite um outro valor: '))
print('O número digitado foi {} e a sua porção inteira é {}'.format(num, trunc(num1)))

num2 = float(input('Digite algum número: '))
print('O valor digitado foi {} e a sua parte inteira é {}'.format(num2, int(num2)))