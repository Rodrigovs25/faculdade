class Conjunto:
    def __init__(self):
        self.elementos = []

    def ehVazio(self):
        return len(self.elementos) == 0

    def uniaoConj(self, outroConj):
        resultado = Conjunto()
        resultado.elementos = self.elementos.copy()
        for elemento in outroConj.elementos:
            if elemento not in resultado.elementos:
                resultado.elementos.append(elemento)
        return resultado

    def intersConj(self, outroConj):
        resultado = Conjunto()
        for elemento in self.elementos:
            if elemento in outroConj.elementos:
                resultado.elementos.append(elemento)
        return resultado

    def diffConj(self, outroConj):
        resultado = Conjunto()
        for elemento in self.elementos:
            if elemento not in outroConj.elementos:
                resultado.elementos.append(elemento)
        return resultado

    def diffSimConj(self, outroConj):
        uniao = self.uniaoConj(outroConj)
        intersecao = self.intersConj(outroConj)
        return uniao.diffConj(intersecao)

    def addConj(self, x):
        if x not in self.elementos:
            self.elementos.append(x)

    def remConj(self, x):
        if x in self.elementos:
            self.elementos.remove(x)

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
print(conjuntoA.uniaoConj(conjuntoB).elementos)  # [1, 2, 3]
print(conjuntoA.intersConj(conjuntoB).elementos)  # [2]
print(conjuntoA.diffConj(conjuntoB).elementos)  # [1]
print(conjuntoA.diffSimConj(conjuntoB).elementos)  # [1, 3]
print(conjuntoA.tamConj())  # 2
print(conjuntoA.ehElemConj(1))  # True
"""
C = Conjunto()
        D = Conjunto()
        for i in A.lista:
            if i in B.lista:
                continue    
            C.addConj(i)
        
        for i in B.lista:
            if i in A.lista:
                continue    
            C.addConj(i)

        C.lista.sort()
"""