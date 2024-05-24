a = float(input('Quanto dinheiro você tem? R$'))
print('Com R${:.2f} você pode comprar US${:.2f}'.format(a, a/5.23))
print('Com R${:.2f} você pode comprar E${:.2f}'.format(a, a/6.1))
print('Com US${:.2f} você pode comprar E${:.2f}'.format(a/5.23, (a/5.23)/(6.1/5.23)))
