import math
an = float(input('Digite o ângulo: '))
seno = math.sin(math.radians(an))
cos = math.cos(math.radians(an))
tan = math.tan(math.radians(an))
print('O ângulo {} tem valor de seno igual a {:.2f}'.format(an, seno))
print('O ângulo {} tem valor de cosseno igual a {:.2f}'.format(an, cos))
print('O ângulo {} tem valor de tangente igual a {:.2f}'.format(an, tan))

from math import sin, cos, tan, radians
an = float(input('Digite o ângulo: '))
seno = sin(radians(an))
cos = cos(radians(an))
tan = tan(radians(an))
print('O ângulo {} tem valor de seno igual a {:.2f}'.format(an, seno))
print('O ângulo {} tem valor de cosseno igual a {:.2f}'.format(an, cos))
print('O ângulo {} tem valor de tangente igual a {:.2f}'.format(an, tan))
