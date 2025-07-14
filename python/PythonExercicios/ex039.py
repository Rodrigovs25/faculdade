from datetime import date
sexo = int(input('''Informe seu sexo:
 [1] Masculino
 [2] Feminino
 Opção:'''  ))
if sexo == 1:
    ano = int(input('Ano de nascimento: '))
    hoje = date.today().year
    idade = hoje - ano
    print('Quem nasceu em {} tem {} em {}'.format(ano, idade, hoje))
    if idade < 18:
        print('Faltam {} anos para o seu alistamento'.format(18 - idade))
        print('Seu alistamneto será em {}'.format(ano + 18))
    elif idade == 18:
        print('Você tem que alistar IMENDIATAMNETE')
    elif idade > 18:
        x = idade - 18
        print('Você já deveria ter se alistado há {} anos'.format(x))
        print('Seu alistamento foi em {} '.format(hoje - x))
elif sexo == 2:
    print('Você não precisa se alistar')
