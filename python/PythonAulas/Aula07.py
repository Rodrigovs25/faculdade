"""
Operadores:
+  adição
-  substração
*  multiplicação
/  divisão -> pode dar número float
** potência
// divisão inteira -> somente número inteira
%  resto da divisão
== igual
=  atribuição

Ordem de precendência:
1 -- ()
2 -- **
3 -- * , / , // , %
4 -- + , -

Anotações:
4**3 = 64
pow(4,3) = 64 --> função de potência
81**(1/2) --> cálculo de raiz quadrada
'oi'*5 = 'oioioioioi'

"""
# nome = str(input('Qual é o seu nome?'))
# print('Prazer em te conhecer {:>20}!'.format(nome))

# a = input('Digite uma palavra:')
# print('A palavra digitada foi {:=^20}.'.format(a))

n1 = int(input('Um valor:'))
n2 = int(input('Outro valor:'))
s = n1 + n2
m = n1 * n2
d = n1 / n2
di = n1 // n2
e = n1 ** n2
print('A soma é {}, \no produto é {} e a divisão é {:.3f}'.format(s, m, d), end=' ')
print('A divisão direta é {} e a potência é {}'.format(di, e))
# end=' '  --> juntar as linhas do print
# \n quebrar a linha no meio no print
# {:.2f} --> duas casas decimais dps da vírgula

