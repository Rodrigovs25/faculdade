class Conjunto:
    def __init__(self):
        self.lista = set()

    def ehVazio(self):
        return not self.lista

    def uniaoConj(self, conjuntoB):
        conjunto_resultante = Conjunto()
        conjunto_resultante.lista = list(set(self.lista) | set(conjuntoB.lista))
        return conjunto_resultante
        

    def intersConj(self, conjuntoB):
        conjunto_resultante = Conjunto()
        conjunto_resultante.lista = list(set(self.lista) & set(conjuntoB.lista))
        return conjunto_resultante

    def diffConj(self, conjuntoB):
        conjunto_resultante = Conjunto()
        conjunto_resultante.lista = list(set(self.lista) - set(conjuntoB.lista))
        return conjunto_resultante

    def diffSimConj(self, conjuntoB):
        conjunto_resultante = Conjunto()
        conjunto_resultante.lista = list(set(self.lista) ^ set(conjuntoB.lista))
        return conjunto_resultante

    def addConj(self, elemento):
        if elemento not in self.lista:
            self.lista.append(elemento)

    def remConj(self, elemento):
        if elemento in self.lista:
            self.lista.remove(elemento)

    def tamConj(self):
        return len(self.lista)

    def ehElemConj(self, elemento):
        return elemento in self.lista

# Exemplo de uso:
conjuntoA = Conjunto()
conjuntoB = Conjunto()

conjuntoA.addConj(1)
conjuntoA.addConj(2)
conjuntoA.addConj(3)

conjuntoB.addConj(2)
conjuntoB.addConj(3)
conjuntoB.addConj(4)

print("Conjunto A: ", conjuntoA.lista)
print("Conjunto B: ", conjuntoB.lista)

print("É vazio? ", conjuntoA.ehVazio())
print("União: ", conjuntoA.uniaoConj(conjuntoB).lista)
print("Interseção: ", conjuntoA.intersConj(conjuntoB).lista)
print("Diferença: ", conjuntoA.diffConj(conjuntoB).lista)
print("Diferença Simétrica: ", conjuntoA.diffSimConj(conjuntoB).lista)
print("Tamanho: ", conjuntoA.tamConj())
print("Contém o elemento 2? ", conjuntoA.ehElemConj(2))
