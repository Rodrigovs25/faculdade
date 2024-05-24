a = float(input('Digite o valor em metro:'))
print('A medida de {}.0m correspode a \n{}km \n{}hm \n{}dam '.format(a, (a*0.001), (a*0.01), (a*0.1)))
print('{}dm \n{}cm \n{}mm'.format((a*10), (a*100), (a*1000)))
