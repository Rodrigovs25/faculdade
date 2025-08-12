from Conjunto import Conjunto

#Criação de Conjuntos:
conjuntoA = Conjunto()
conjuntoB = Conjunto()

#Adição de Elementos:
conjuntoA.addConj(1)
conjuntoA.addConj(2)
conjuntoA.addConj(3)
conjuntoA.addConj(5)

conjuntoB.addConj(2)
conjuntoB.addConj(3)
conjuntoB.addConj(4)

#Impressão:
print("Conjunto A: ", conjuntoA.lista)
print("Conjunto B: ", conjuntoB.lista)

#Operações entre Conjuntos:
uniao = conjuntoA.uniaoConj(conjuntoB)
print("União: ", uniao.lista)
intersecao = conjuntoA.intersConj(conjuntoB)
print("Interseção: ", intersecao.lista)
diferenca = conjuntoA.diffConj(conjuntoB)
print("Diferença entre A e B: ", diferenca.lista)
dif_sim = conjuntoA.diffSimConj(conjuntoB)
print("Diferença Simétrica entre A e B: ", dif_sim.lista)

#Verificação e Manipulação:
print("É vazio? ", conjuntoA.ehVazio())
print("Tamanho: ", conjuntoA.tamConj())
print("Contém o elemento 2? ", conjuntoA.ehElemConj(2))
conjuntoA.remConj(2)
print("Conjunto A: ", conjuntoA.lista)


