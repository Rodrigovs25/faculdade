class Conjunto:
    def __init__(self):
        self.elementos = set()

    def ehVazio(self):
        return not self.elementos

    def uniaoConj(self, outroConj):
        return self.elementos.union(outroConj.elementos)

    def intersConj(self, outroConj):
        return self.elementos.intersection(outroConj.elementos)

    def diffConj(self, outroConj):
        return self.elementos.difference(outroConj.elementos)

    def diffSimConj(self, outroConj):
        return self.elementos.symmetric_difference(outroConj.elementos)

    def addConj(self, x):
        self.elementos.add(x)

    def remConj(self, x):
        self.elementos.discard(x)

    def tamConj(self):
        return len(self.elementos)

    def ehElemConj(self, x):
        return x in self.elementos


# Exemplo de uso
conjuntoA = Conjunto()
conjuntoB = Conjunto()

conjuntoA.addConj(1)
conjuntoA.addConj(2)
conjuntoB.addConj(2)
conjuntoB.addConj(3)

print(conjuntoA.ehVazio())  # False
print(conjuntoA.uniaoConj(conjuntoB))  # {1, 2, 3}
print(conjuntoA.intersConj(conjuntoB))  # {2}
print(conjuntoA.diffConj(conjuntoB))  # {1}
print(conjuntoA.diffSimConj(conjuntoB))  # {1, 3}
print(conjuntoA.tamConj())  # 2
print(conjuntoA.ehElemConj(1))  # True
