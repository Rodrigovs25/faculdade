a = float(input('Largura da parede: '))
b = float(input('Altura da parede: '))
print('Sua parede tem dimensão de{}x{} e sua área é de {}.'.format(a, b, a*b))
print('Para pintar essa parede, você precisará de {}L de tinta.'.format((a*b)/2))