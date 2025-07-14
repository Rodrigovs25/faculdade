"""
CONDIÇÕES ANINHADAS:
if xxxx:
elif xxxx: --> else if
elif xxxx:
else:
"""
nome = str(input('Qual é seu nome? '))
if nome == 'Rodrigo':
    print('Que nome lindo')
elif nome == 'Pedro' or nome == 'Maria' or nome =='Paulo':
    print('Seu nome é bem popular do brasil')
elif nome in 'Ana Claúdia Jéssica Juliana':
    print('Que belo nome feminino')
else:
    print('Your name is really common')
print('Tenha um bom dia {}'.format(nome))
